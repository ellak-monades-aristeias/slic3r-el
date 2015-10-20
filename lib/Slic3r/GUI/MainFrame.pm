package Slic3r::GUI::MainFrame;
use strict;
use warnings;
use utf8;

use File::Basename qw(basename dirname);
use List::Util qw(min);
use Slic3r::Geometry qw(X Y Z);
use Wx qw(:frame :bitmap :id :misc :notebook :panel :sizer :menu :dialog :filedialog
    :font :icon wxTheApp);
use Wx::Event qw(EVT_CLOSE EVT_MENU);
use base 'Wx::Frame';

our $qs_last_input_file;
our $qs_last_output_file;
our $last_config;

sub new {
    my ($class, %params) = @_;
    
    my $self = $class->SUPER::new(undef, -1, 'Slic3r', wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE);
    $self->SetIcon(Wx::Icon->new("$Slic3r::var/Slic3r_128px.png", wxBITMAP_TYPE_PNG) );
    
    # store input params
    $self->{mode} = $params{mode};
    $self->{mode} = 'expert' if $self->{mode} !~ /^(?:simple|expert)$/;
    $self->{no_plater} = $params{no_plater};
    $self->{loaded} = 0;
    
    # initialize tabpanel and menubar
    $self->_init_tabpanel;
    $self->_init_menubar;
    
    # initialize status bar
    $self->{statusbar} = Slic3r::GUI::ProgressStatusBar->new($self, -1);
    $self->{statusbar}->SetStatusText("Έκδοση $Slic3r::VERSION - Θυμηθείτε να ελέγξετε για ενημερωεις στη διεύθυνση http://slic3r.org/");
    $self->SetStatusBar($self->{statusbar});
    
    $self->{loaded} = 1;
    
    # initialize layout
    {
        my $sizer = Wx::BoxSizer->new(wxVERTICAL);
        $sizer->Add($self->{tabpanel}, 1, wxEXPAND);
        $sizer->SetSizeHints($self);
        $self->SetSizer($sizer);
        $self->Fit;
        $self->SetMinSize([760, 490]);
        if (defined $Slic3r::GUI::Settings->{_}{main_frame_size}) {
            my $size = [ split ',', $Slic3r::GUI::Settings->{_}{main_frame_size}, 2 ];
            $self->SetSize($size);
            
            my $display = Wx::Display->new->GetClientArea();
            my $pos = [ split ',', $Slic3r::GUI::Settings->{_}{main_frame_pos}, 2 ];
            if (($pos->[X] + $size->[X]/2) < $display->GetRight && ($pos->[Y] + $size->[Y]/2) < $display->GetBottom) {
                $self->Move($pos);
            }
            $self->Maximize(1) if $Slic3r::GUI::Settings->{_}{main_frame_maximized};
        } else {
            $self->SetSize($self->GetMinSize);
        }
        $self->Show;
        $self->Layout;
    }
    
    # declare events
    EVT_CLOSE($self, sub {
        my (undef, $event) = @_;
        
        if ($event->CanVeto && !$self->check_unsaved_changes) {
            $event->Veto;
            return;
        }
        
        # save window size
        $Slic3r::GUI::Settings->{_}{main_frame_pos}  = join ',', $self->GetScreenPositionXY;
        $Slic3r::GUI::Settings->{_}{main_frame_size} = join ',', $self->GetSizeWH;
        $Slic3r::GUI::Settings->{_}{main_frame_maximized} = $self->IsMaximized;
        wxTheApp->save_settings;
        
        # propagate event
        $event->Skip;
    });
    
    return $self;
}

sub _init_tabpanel {
    my ($self) = @_;
    
    $self->{tabpanel} = my $panel = Wx::Notebook->new($self, -1, wxDefaultPosition, wxDefaultSize, wxNB_TOP | wxTAB_TRAVERSAL);
    
    if (!$self->{no_plater}) {
        $panel->AddPage($self->{plater} = Slic3r::GUI::Plater->new($panel), "Πλατφόρμα");
    }
    $self->{options_tabs} = {};
    
    my $simple_config;
    if ($self->{mode} eq 'simple') {
        $simple_config = Slic3r::Config->load("$Slic3r::GUI::datadir/simple.ini")
            if -e Slic3r::encode_path("$Slic3r::GUI::datadir/simple.ini");
    }
    
    my $class_prefix = $self->{mode} eq 'simple' ? "Slic3r::GUI::SimpleTab::" : "Slic3r::GUI::Tab::";
    for my $tab_name (qw(print filament printer)) {
        my $tab;
        $tab = $self->{options_tabs}{$tab_name} = ($class_prefix . ucfirst $tab_name)->new($panel);
        $tab->on_value_change(sub {
            my ($opt_key, $value) = @_;
            
            my $config = $tab->config;
            if ($self->{plater}) {
                $self->{plater}->on_config_change($config); # propagate config change events to the plater
                $self->{plater}->on_extruders_change($value) if $opt_key eq 'extruders_count';
            }
            if ($self->{loaded}) {  # don't save while loading for the first time
                if ($self->{mode} eq 'simple') {
                    # save config
                    $self->config->save("$Slic3r::GUI::datadir/simple.ini");
                    
                    # save a copy into each preset section
                    # so that user gets the config when switching to expert mode
                    $config->save(sprintf "$Slic3r::GUI::datadir/%s/%s.ini", $tab->name, 'Απλή Λειτουργία');
                    $Slic3r::GUI::Settings->{presets}{$tab->name} = 'Simple Mode.ini';
                    wxTheApp->save_settings;
                }
                $self->config->save($Slic3r::GUI::autosave) if $Slic3r::GUI::autosave;
            }
        });
        $tab->on_presets_changed(sub {
            if ($self->{plater}) {
                $self->{plater}->update_presets($tab_name, @_);
                $self->{plater}->on_config_change($tab->config);
            }
        });
        $tab->load_presets;
        $panel->AddPage($tab, $tab->title);
        $tab->load_config($simple_config) if $simple_config;
    }
    
    if ($self->{plater}) {
        $self->{plater}->on_select_preset(sub {
            my ($group, $i) = @_;
	        $self->{options_tabs}{$group}->select_preset($i);
        });
        
        # load initial config
        $self->{plater}->on_config_change($self->config);
    }
}

sub _init_menubar {
    my ($self) = @_;
    
    # File menu
    my $fileMenu = Wx::Menu->new;
    {
        $self->_append_menu_item($fileMenu, "&Φόρτωση Διαμόρφωσης…\tCtrl+L", 'Φόρτωση εξαγώμενου αρχείου διαμόρφωσης', sub {
            $self->load_config_file;
        }, undef, 'plugin_add.png');
        $self->_append_menu_item($fileMenu, "&Εξαγωγή Διαμόρφωσης…\tCtrl+E", 'Εξαγωγή της τρέχουσας διαμόρφωσης σε αρχείο', sub {
            $self->export_config;
        }, undef, 'plugin_go.png');
        $self->_append_menu_item($fileMenu, "&Φόρτωση Δέσμης Διαμορφώσεων…", 'Φόρτωση των προκαθορισμένων ρυθμίσεων από μία δέσμη', sub {
            $self->load_configbundle;
        }, undef, 'lorry_add.png');
        $self->_append_menu_item($fileMenu, "&Εξαγωγή Δέσμης Διαμορφώσεων…", 'Εξαγωγή όλων των προκαθορισμένων ρυθμίσεων σε αρχείο', sub {
            $self->export_configbundle;
        }, undef, 'lorry_go.png');
        $fileMenu->AppendSeparator();
        my $repeat;
        $self->_append_menu_item($fileMenu, "Γρήγορο Τεμάχισμα…\tCtrl+U", 'Τεμαχισμός αρχείου', sub {
            wxTheApp->CallAfter(sub {
                $self->quick_slice;
                $repeat->Enable(defined $Slic3r::GUI::MainFrame::last_input_file);
            });
        }, undef, 'cog_go.png');
        $self->_append_menu_item($fileMenu, "Γρήγορο Τεμάχισμα και Αποθήκευση ως…\tCtrl+Alt+U", 'Τεμάχισμα αρχείου και αποθήκευση ως', sub {
            wxTheApp->CallAfter(sub {
                $self->quick_slice(save_as => 1);
                $repeat->Enable(defined $Slic3r::GUI::MainFrame::last_input_file);
            });
        }, undef, 'cog_go.png');
        $repeat = $self->_append_menu_item($fileMenu, "&Επανάληψη Τελευταίου Γρήγορου Τεμαχίσματος\tCtrl+Shift+U", 'Επανάληψη τελευταίου γρήγορου τεμαχίσματος', sub {
            wxTheApp->CallAfter(sub {
                $self->quick_slice(reslice => 1);
            });
        }, undef, 'cog_go.png');
        $repeat->Enable(0);
        $fileMenu->AppendSeparator();
        $self->_append_menu_item($fileMenu, "Τεμάχισμα σε SV&G…\tCtrl+G", 'Τεμάχισμα αρχείου σε SVG', sub {
            $self->quick_slice(save_as => 1, export_svg => 1);
        }, undef, 'shape_handles.png');
        $fileMenu->AppendSeparator();
        $self->_append_menu_item($fileMenu, "Διόρθωση αρχείου STL…", 'Αυτόματη διόρθωση ενός αρχείου STL', sub {
            $self->repair_stl;
        }, undef, 'wrench.png');
        $fileMenu->AppendSeparator();
        # Cmd+, is standard on OS X - what about other operating systems?
        $self->_append_menu_item($fileMenu, "Προτιμήσεις…\tCtrl+,", 'Προτιμήσεις εφαρμογής', sub {
            Slic3r::GUI::Preferences->new($self)->ShowModal;
        }, wxID_PREFERENCES);
        $fileMenu->AppendSeparator();
        $self->_append_menu_item($fileMenu, "&Έξοδος", 'Έξοδος από το Slic3r', sub {
            $self->Close(0);
        }, wxID_EXIT);
    }
    
    # Plater menu
    unless ($self->{no_plater}) {
        my $plater = $self->{plater};
        
        $self->{plater_menu} = Wx::Menu->new;
        $self->_append_menu_item($self->{plater_menu}, "Εξαγωγή G-code...", 'Εξαγωγή τρέχουσας πλατφόρμας ως G-code', sub {
            $plater->export_gcode;
        }, undef, 'cog_go.png');
        $self->_append_menu_item($self->{plater_menu}, "Έξαγωγή ως STL...", 'Εξαγωγή τρέχουσας πλατφόρμας ως STL', sub {
            $plater->export_stl;
        }, undef, 'brick_go.png');
        $self->_append_menu_item($self->{plater_menu}, "Εξαγωγή ως AMF...", 'Εξαγωγή τρέχουσας πλατφόρμας ως AMF', sub {
            $plater->export_amf;
        }, undef, 'brick_go.png');
        
        $self->{object_menu} = $self->{plater}->object_menu;
        $self->on_plater_selection_changed(0);
    }
    
    # Window menu
    my $windowMenu = Wx::Menu->new;
    {
        my $tab_count = $self->{no_plater} ? 3 : 4;
        $self->_append_menu_item($windowMenu, "Επιλογή Καρτέλας Πλατφόρμα\tCtrl+1", 'Εμφάνιση Πλατφόρμας', sub {
            $self->select_tab(0);
        }, undef, 'application_view_tile.png') unless $self->{no_plater};
        $self->_append_menu_item($windowMenu, "Επιλογή Καρτέλας Ρυθμίσεις Εκτύπωσης\tCtrl+2", 'Εμφάνιση των ρυθμίσεων εκτύπωσης', sub {
            $self->select_tab($tab_count-3);
        }, undef, 'cog.png');
        $self->_append_menu_item($windowMenu, "Επιλογή Καρτέλας Ρυθμίσεις Υλικού\tCtrl+3", 'Εμφάνιση των ρυθμίσεων υλικού', sub {
            $self->select_tab($tab_count-2);
        }, undef, 'spool.png');
        $self->_append_menu_item($windowMenu, "Επιλογή Καρτέλας Ρυθμίσεις Εκτυπωτή\tCtrl+4", 'Εμφάνιση των ρυθμίσεων εκτυπωτή', sub {
            $self->select_tab($tab_count-1);
        }, undef, 'printer_empty.png');
    }
    
    # Help menu
    my $helpMenu = Wx::Menu->new;
    {
        $self->_append_menu_item($helpMenu, "&Configuration $Slic3r::GUI::ConfigWizard::wizard…", "Run Configuration $Slic3r::GUI::ConfigWizard::wizard", sub {
            $self->config_wizard;
        });
        $helpMenu->AppendSeparator();
        $self->_append_menu_item($helpMenu, "Ιστοσελίδα Slic3r", 'Άνοιγμα της ιστοσελίδας του Slic3r στον περιηγητή σας', sub {
            Wx::LaunchDefaultBrowser('http://slic3r.org/');
        });
        my $versioncheck = $self->_append_menu_item($helpMenu, "Έλεγχος για ενημερώσεις...", 'Έλεγχος για νέες εκδόσεις Slic3r', sub {
            wxTheApp->check_version(1);
        });
        $versioncheck->Enable(wxTheApp->have_version_check);
        $self->_append_menu_item($helpMenu, "Εγχειρίδιο Slic3r", 'Άνοιγμα του εγχειριδίου του Slic3r στον περιηγητή σας', sub {
            Wx::LaunchDefaultBrowser('http://manual.slic3r.org/');
        });
        $helpMenu->AppendSeparator();
        $self->_append_menu_item($helpMenu, "&Σχετικά με το Slic3r", 'Εμφάνιση του παραθύρου Σχετικά με', sub {
            wxTheApp->about;
        });
    }
    
    # menubar
    # assign menubar to frame after appending items, otherwise special items
    # will not be handled correctly
    {
        my $menubar = Wx::MenuBar->new;
        $menubar->Append($fileMenu, "&Αρχείο");
        $menubar->Append($self->{plater_menu}, "&Πλατφόρμα") if $self->{plater_menu};
        $menubar->Append($self->{object_menu}, "&Αντικείμενο") if $self->{object_menu};
        $menubar->Append($windowMenu, "&Παράθυρο");
        $menubar->Append($helpMenu, "&Βοήθεια");
        $self->SetMenuBar($menubar);
    }
}

sub is_loaded {
    my ($self) = @_;
    return $self->{loaded};
}

sub on_plater_selection_changed {
    my ($self, $have_selection) = @_;
    
    return if !defined $self->{object_menu};
    $self->{object_menu}->Enable($_->GetId, $have_selection)
        for $self->{object_menu}->GetMenuItems;
}

sub quick_slice {
    my $self = shift;
    my %params = @_;
    
    my $progress_dialog;
    eval {
        # validate configuration
        my $config = $self->config;
        $config->validate;
        
        # select input file
        my $input_file;
        my $dir = $Slic3r::GUI::Settings->{recent}{skein_directory} || $Slic3r::GUI::Settings->{recent}{config_directory} || '';
        if (!$params{reslice}) {
            my $dialog = Wx::FileDialog->new($self, 'Επιλέξτε αρχείο για τεμαχισμό (STL/OBJ/AMF):', $dir, "", &Slic3r::GUI::MODEL_WILDCARD, wxFD_OPEN | wxFD_FILE_MUST_EXIST);
            if ($dialog->ShowModal != wxID_OK) {
                $dialog->Destroy;
                return;
            }
            $input_file = Slic3r::decode_path($dialog->GetPaths);
            $dialog->Destroy;
            $qs_last_input_file = $input_file unless $params{export_svg};
        } else {
            if (!defined $qs_last_input_file) {
                Wx::MessageDialog->new($self, "Κανένα προηγούμενο τεμαχισμένο αχείο.",
                                       'Error', wxICON_ERROR | wxOK)->ShowModal();
                return;
            }
            if (! -e $qs_last_input_file) {
                Wx::MessageDialog->new($self, "Δεν βρέθηκε προηγουμένως τεμαχισμένο αρχείο ($qs_last_input_file).",
                                       'Το αρχείο δεν βρέθηκε', wxICON_ERROR | wxOK)->ShowModal();
                return;
            }
            $input_file = $qs_last_input_file;
        }
        my $input_file_basename = basename($input_file);
        $Slic3r::GUI::Settings->{recent}{skein_directory} = dirname($input_file);
        wxTheApp->save_settings;
        
        my $print_center;
        {
            my $bed_shape = Slic3r::Polygon->new_scale(@{$config->bed_shape});
            $print_center = Slic3r::Pointf->new_unscale(@{$bed_shape->bounding_box->center});
        }
        
        my $sprint = Slic3r::Print::Simple->new(
            print_center    => $print_center,
            status_cb       => sub {
                my ($percent, $message) = @_;
                return if &Wx::wxVERSION_STRING !~ / 2\.(8\.|9\.[2-9])/;
                $progress_dialog->Update($percent, "$message…");
            },
        );
        
        # keep model around
        my $model = Slic3r::Model->read_from_file($input_file);
        
        $sprint->apply_config($config);
        $sprint->set_model($model);
        
        {
            my $extra = $self->extra_variables;
            $sprint->placeholder_parser->set($_, $extra->{$_}) for keys %$extra;
        }
        
        # select output file
        my $output_file;
        if ($params{reslice}) {
            $output_file = $qs_last_output_file if defined $qs_last_output_file;
        } elsif ($params{save_as}) {
            $output_file = $sprint->expanded_output_filepath;
            $output_file =~ s/\.gcode$/.svg/i if $params{export_svg};
            my $dlg = Wx::FileDialog->new($self, 'Αποθήκευση ' . ($params{export_svg} ? 'SVG' : 'G-code') . ' αρχείου ως:',
                wxTheApp->output_path(dirname($output_file)),
                basename($output_file), $params{export_svg} ? &Slic3r::GUI::FILE_WILDCARDS->{svg} : &Slic3r::GUI::FILE_WILDCARDS->{gcode}, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
            if ($dlg->ShowModal != wxID_OK) {
                $dlg->Destroy;
                return;
            }
            $output_file = Slic3r::decode_path($dlg->GetPath);
            $qs_last_output_file = $output_file unless $params{export_svg};
            $Slic3r::GUI::Settings->{_}{last_output_path} = dirname($output_file);
            wxTheApp->save_settings;
            $dlg->Destroy;
        }
        
        # show processbar dialog
        $progress_dialog = Wx::ProgressDialog->new('Τεμαχισμός…', "Επεξεργασία $input_file_basename…", 
            100, $self, 0);
        $progress_dialog->Pulse;
        
        {
            my @warnings = ();
            local $SIG{__WARN__} = sub { push @warnings, $_[0] };
            
            $sprint->output_file($output_file);
            if ($params{export_svg}) {
                $sprint->export_svg;
            } else {
                $sprint->export_gcode;
            }
            $sprint->status_cb(undef);
            Slic3r::GUI::warning_catcher($self)->($_) for @warnings;
        }
        $progress_dialog->Destroy;
        undef $progress_dialog;
        
        my $message = "$input_file_basename τεμαχίστηκε επιτυχώς.";
        wxTheApp->notify($message);
        Wx::MessageDialog->new($self, $message, 'Ο Τεμαχισμός Ολοκληρώθηκε!', 
            wxOK | wxICON_INFORMATION)->ShowModal;
    };
    Slic3r::GUI::catch_error($self, sub { $progress_dialog->Destroy if $progress_dialog });
}

sub repair_stl {
    my $self = shift;
    
    my $input_file;
    {
        my $dir = $Slic3r::GUI::Settings->{recent}{skein_directory} || $Slic3r::GUI::Settings->{recent}{config_directory} || '';
        my $dialog = Wx::FileDialog->new($self, 'Επιλέξτε το αρχείο STL για τη διόρθωση:', $dir, "", &Slic3r::GUI::FILE_WILDCARDS->{stl}, wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        if ($dialog->ShowModal != wxID_OK) {
            $dialog->Destroy;
            return;
        }
        $input_file = Slic3r::decode_path($dialog->GetPaths);
        $dialog->Destroy;
    }
    
    my $output_file = $input_file;
    {
        $output_file =~ s/\.stl$/_fixed.obj/i;
        my $dlg = Wx::FileDialog->new($self, "Αποθήκευση αρχείου OBJ (λιγότερο επιρρεπείς στο να συντονίσουν τα λάθη σε σχέση με STL) ως:", dirname($output_file),
            basename($output_file), &Slic3r::GUI::FILE_WILDCARDS->{obj}, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
        if ($dlg->ShowModal != wxID_OK) {
            $dlg->Destroy;
            return undef;
        }
        $output_file = Slic3r::decode_path($dlg->GetPath);
        $dlg->Destroy;
    }
    
    my $tmesh = Slic3r::TriangleMesh->new;
    $tmesh->ReadSTLFile(Slic3r::encode_path($input_file));
    $tmesh->repair;
    $tmesh->WriteOBJFile(Slic3r::encode_path($output_file));
    Slic3r::GUI::show_info($self, "Το αρχείο σας διορθώθηκε.", "Διόρθωση");
}

sub extra_variables {
    my $self = shift;
    
    my %extra_variables = ();
    if ($self->{mode} eq 'expert') {
        $extra_variables{"${_}_preset"} = $self->{options_tabs}{$_}->get_current_preset->name
            for qw(print filament printer);
    }
    return { %extra_variables };
}

sub export_config {
    my $self = shift;
    
    my $config = $self->config;
    eval {
        # validate configuration
        $config->validate;
    };
    Slic3r::GUI::catch_error($self) and return;
    
    my $dir = $last_config ? dirname($last_config) : $Slic3r::GUI::Settings->{recent}{config_directory} || $Slic3r::GUI::Settings->{recent}{skein_directory} || '';
    my $filename = $last_config ? basename($last_config) : "config.ini";
    my $dlg = Wx::FileDialog->new($self, 'Αποθήκευση διαμόρφωσης ως:', $dir, $filename, 
        &Slic3r::GUI::FILE_WILDCARDS->{ini}, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if ($dlg->ShowModal == wxID_OK) {
        my $file = Slic3r::decode_path($dlg->GetPath);
        $Slic3r::GUI::Settings->{recent}{config_directory} = dirname($file);
        wxTheApp->save_settings;
        $last_config = $file;
        $config->save($file);
    }
    $dlg->Destroy;
}

sub load_config_file {
    my $self = shift;
    my ($file) = @_;
    
    if (!$file) {
        return unless $self->check_unsaved_changes;
        my $dir = $last_config ? dirname($last_config) : $Slic3r::GUI::Settings->{recent}{config_directory} || $Slic3r::GUI::Settings->{recent}{skein_directory} || '';
        my $dlg = Wx::FileDialog->new($self, 'Επιλογή διαμόρφωσης προς φόρτωση:', $dir, "config.ini", 
                &Slic3r::GUI::FILE_WILDCARDS->{ini}, wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        return unless $dlg->ShowModal == wxID_OK;
        $file = Slic3r::decode_path($dlg->GetPaths);
        $dlg->Destroy;
    }
    $Slic3r::GUI::Settings->{recent}{config_directory} = dirname($file);
    wxTheApp->save_settings;
    $last_config = $file;
    for my $tab (values %{$self->{options_tabs}}) {
        $tab->load_config_file($file);
    }
}

sub export_configbundle {
    my $self = shift;
    
    eval {
        # validate current configuration in case it's dirty
        $self->config->validate;
    };
    Slic3r::GUI::catch_error($self) and return;
    
    my $dir = $last_config ? dirname($last_config) : $Slic3r::GUI::Settings->{recent}{config_directory} || $Slic3r::GUI::Settings->{recent}{skein_directory} || '';
    my $filename = "Slic3r_config_bundle.ini";
    my $dlg = Wx::FileDialog->new($self, 'Αποθήκευση δέσμης προεπιλογών ως:', $dir, $filename, 
        &Slic3r::GUI::FILE_WILDCARDS->{ini}, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if ($dlg->ShowModal == wxID_OK) {
        my $file = Slic3r::decode_path($dlg->GetPath);
        $Slic3r::GUI::Settings->{recent}{config_directory} = dirname($file);
        wxTheApp->save_settings;
        
        # leave default category empty to prevent the bundle from being parsed as a normal config file
        my $ini = { _ => {} };
        $ini->{settings}{$_} = $Slic3r::GUI::Settings->{_}{$_} for qw(autocenter mode);
        $ini->{presets} = $Slic3r::GUI::Settings->{presets};
        if (-e "$Slic3r::GUI::datadir/simple.ini") {
            my $config = Slic3r::Config->load("$Slic3r::GUI::datadir/simple.ini");
            $ini->{simple} = $config->as_ini->{_};
        }
        
        foreach my $section (qw(print filament printer)) {
            my %presets = wxTheApp->presets($section);
            foreach my $preset_name (keys %presets) {
                my $config = Slic3r::Config->load($presets{$preset_name});
                $ini->{"$section:$preset_name"} = $config->as_ini->{_};
            }
        }
        
        Slic3r::Config->write_ini($file, $ini);
    }
    $dlg->Destroy;
}

sub load_configbundle {
    my $self = shift;
    
    my $dir = $last_config ? dirname($last_config) : $Slic3r::GUI::Settings->{recent}{config_directory} || $Slic3r::GUI::Settings->{recent}{skein_directory} || '';
    my $dlg = Wx::FileDialog->new($self, 'Επιλογή διαμόρφωσης προς φόρτωση:', $dir, "config.ini", 
            &Slic3r::GUI::FILE_WILDCARDS->{ini}, wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    return unless $dlg->ShowModal == wxID_OK;
    my $file = Slic3r::decode_path($dlg->GetPaths);
    $dlg->Destroy;
    
    $Slic3r::GUI::Settings->{recent}{config_directory} = dirname($file);
    wxTheApp->save_settings;
    
    # load .ini file
    my $ini = Slic3r::Config->read_ini($file);
    
    if ($ini->{settings}) {
        $Slic3r::GUI::Settings->{_}{$_} = $ini->{settings}{$_} for keys %{$ini->{settings}};
        wxTheApp->save_settings;
    }
    if ($ini->{presets}) {
        $Slic3r::GUI::Settings->{presets} = $ini->{presets};
        wxTheApp->save_settings;
    }
    if ($ini->{simple}) {
        my $config = Slic3r::Config->load_ini_hash($ini->{simple});
        $config->save("$Slic3r::GUI::datadir/simple.ini");
        if ($self->{mode} eq 'simple') {
            foreach my $tab (values %{$self->{options_tabs}}) {
                $tab->load_config($config) for values %{$self->{options_tabs}};
            }
        }
    }
    my $imported = 0;
    foreach my $ini_category (sort keys %$ini) {
        next unless $ini_category =~ /^(print|filament|printer):(.+)$/;
        my ($section, $preset_name) = ($1, $2);
        my $config = Slic3r::Config->load_ini_hash($ini->{$ini_category});
        $config->save(sprintf "$Slic3r::GUI::datadir/%s/%s.ini", $section, $preset_name);
        $imported++;
    }
    if ($self->{mode} eq 'expert') {
        foreach my $tab (values %{$self->{options_tabs}}) {
            $tab->load_presets;
        }
    }
    my $message = sprintf "%d διαμορφώσεις εισήχθησαν επιτυχώς.", $imported;
    if ($self->{mode} eq 'simple' && $Slic3r::GUI::Settings->{_}{mode} eq 'expert') {
        Slic3r::GUI::show_info($self, "$message Πρέπει να επανεκκινήσετε το Slic3r για να εφαρμοστούν οι αλλαγές.");
    } else {
        Slic3r::GUI::show_info($self, $message);
    }
}

sub load_config {
    my $self = shift;
    my ($config) = @_;
    
    foreach my $tab (values %{$self->{options_tabs}}) {
        $tab->load_config($config);
    }
    if ($self->{plater}) {
        $self->{plater}->on_config_change($config);
    }
}

sub config_wizard {
    my $self = shift;

    return unless $self->check_unsaved_changes;
    if (my $config = Slic3r::GUI::ConfigWizard->new($self)->run) {
        if ($self->{mode} eq 'expert') {
            for my $tab (values %{$self->{options_tabs}}) {
                $tab->select_default_preset;
            }
        } else {
            # TODO: select default settings in simple mode
        }
        $self->load_config($config);
        if ($self->{mode} eq 'expert') {
            for my $tab (values %{$self->{options_tabs}}) {
                $tab->save_preset('My Settings');
            }
        }
    }
}

=head2 config

This method collects all config values from the tabs and merges them into a single config object.

=cut

sub config {
    my $self = shift;
    
    return Slic3r::Config->new_from_defaults
        if !exists $self->{options_tabs}{print}
            || !exists $self->{options_tabs}{filament}
            || !exists $self->{options_tabs}{printer};
    
    # retrieve filament presets and build a single config object for them
    my $filament_config;
    if (!$self->{plater} || $self->{plater}->filament_presets == 1 || $self->{mode} eq 'simple') {
        $filament_config = $self->{options_tabs}{filament}->config;
    } else {
        my $i = -1;
        foreach my $preset_idx ($self->{plater}->filament_presets) {
            $i++;
            my $config;
            if ($preset_idx == $self->{options_tabs}{filament}->current_preset) {
                # the selected preset for this extruder is the one in the tab
                # use the tab's config instead of the preset in case it is dirty
                # perhaps plater shouldn't expose dirty presets at all in multi-extruder environments.
                $config = $self->{options_tabs}{filament}->config;
            } else {
                my $preset = $self->{options_tabs}{filament}->get_preset($preset_idx);
                $config = $self->{options_tabs}{filament}->get_preset_config($preset);
            }
            if (!$filament_config) {
                $filament_config = $config->clone;
                next;
            }
            foreach my $opt_key (@{$config->get_keys}) {
                my $value = $filament_config->get($opt_key);
                next unless ref $value eq 'ARRAY';
                $value->[$i] = $config->get($opt_key)->[0];
                $filament_config->set($opt_key, $value);
            }
        }
    }
    
    my $config = Slic3r::Config->merge(
        Slic3r::Config->new_from_defaults,
        $self->{options_tabs}{print}->config,
        $self->{options_tabs}{printer}->config,
        $filament_config,
    );
    
    if ($self->{mode} eq 'simple') {
        # set some sensible defaults
        $config->set('first_layer_height', $config->nozzle_diameter->[0]);
        $config->set('avoid_crossing_perimeters', 1);
        $config->set('infill_every_layers', 10);
    } else {
        my $extruders_count = $self->{options_tabs}{printer}{extruders_count};
        $config->set("${_}_extruder", min($config->get("${_}_extruder"), $extruders_count))
            for qw(perimeter infill solid_infill support_material support_material_interface);
    }
    
    return $config;
}

sub check_unsaved_changes {
    my $self = shift;
    
    my @dirty = ();
    foreach my $tab (values %{$self->{options_tabs}}) {
        push @dirty, $tab->title if $tab->is_dirty;
    }
    
    if (@dirty) {
        my $titles = join ', ', @dirty;
        my $confirm = Wx::MessageDialog->new($self, "Έχετε μη αποθηκευμένες αλλαγές ($titles). Απόρριψη αλλαγών και συνέχεια?",
                                             'Μη αποθυκευμένες Προτιμήσεις', wxICON_QUESTION | wxYES_NO | wxNO_DEFAULT);
        return ($confirm->ShowModal == wxID_YES);
    }
    
    return 1;
}

sub select_tab {
    my ($self, $tab) = @_;
    $self->{tabpanel}->ChangeSelection($tab);
}

sub _append_menu_item {
    my ($self, $menu, $string, $description, $cb, $id, $icon) = @_;
    
    $id //= &Wx::NewId();
    my $item = $menu->Append($id, $string, $description);
    $self->_set_menu_item_icon($item, $icon);
    
    EVT_MENU($self, $id, $cb);
    return $item;
}

sub _set_menu_item_icon {
    my ($self, $menuItem, $icon) = @_;
    
    # SetBitmap was not available on OS X before Wx 0.9927
    if ($icon && $menuItem->can('SetBitmap')) {
        $menuItem->SetBitmap(Wx::Bitmap->new("$Slic3r::var/$icon", wxBITMAP_TYPE_PNG));
    }
}

1;
