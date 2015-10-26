package Slic3r::GUI::Preferences;
use Wx qw(:dialog :id :misc :sizer :systemsettings wxTheApp);
use Wx::Event qw(EVT_BUTTON EVT_TEXT_ENTER);
use base 'Wx::Dialog';
use utf8;

sub new {
    my ($class, $parent) = @_;
    my $self = $class->SUPER::new($parent, -1, "Προτιμήσεις", wxDefaultPosition, wxDefaultSize);
    $self->{values} = {};
    
    my $optgroup;
    $optgroup = Slic3r::GUI::OptionsGroup->new(
        parent  => $self,
        title   => 'Γενικά',
        on_change => sub {
            my ($opt_id) = @_;
            $self->{values}{$opt_id} = $optgroup->get_value($opt_id);
        },
        label_width => 200,
    );
    $optgroup->append_single_option_line(Slic3r::GUI::OptionsGroup::Option->new(
        opt_id      => 'mode',
        type        => 'select',
        label       => 'Λειτουργία',
        tooltip     => 'Επιλέξτε ανάμεσα σε μια απλούστερη , βασική λειτουργία και μια εξειδικευμένη λειτουργία , με περισσότερες επιλογές και πιο περίπλοκο περιβάλλον.',
        labels      => ['Απλή','Εξειδικευμένη'],
        values      => ['simple','expert'],
        default     => $Slic3r::GUI::Settings->{_}{mode},
        width       => 100,
    ));
    $optgroup->append_single_option_line(Slic3r::GUI::OptionsGroup::Option->new(
        opt_id      => 'version_check',
        type        => 'bool',
        label       => 'Έλεγχος για ενημερώσεις',
        tooltip     => 'Αν αυτή η επιλογή είναι ενεργοποιημένη, το Slic3r θα ελέγχει για ενημερώσεις καθημερινά και να εμφανίσει μια υπενθύμιση εάν μια νεότερη έκδοση είναι διαθέσιμη.',
        default     => $Slic3r::GUI::Settings->{_}{version_check} // 1,
        readonly    => !wxTheApp->have_version_check,
    ));
    $optgroup->append_single_option_line(Slic3r::GUI::OptionsGroup::Option->new(
        opt_id      => 'remember_output_path',
        type        => 'bool',
        label       => 'Απομνημόνευση του καταλόγου εξόδου',
        tooltip     => 'Αν αυτή η επιλογή είναι ενεργοποιημένη, το Slic3r θα προτρέπει τον τελευταίο κατάλογο εξόδου αντί του καταλόγου που περιέχει τα αρχεία εισόδου.',
        default     => $Slic3r::GUI::Settings->{_}{remember_output_path},
    ));
    $optgroup->append_single_option_line(Slic3r::GUI::OptionsGroup::Option->new(
        opt_id      => 'autocenter',
        type        => 'bool',
        label       => 'Αυτόματο κεντράρισμα κομματιών',
        tooltip     => 'Αν αυτή η επιλογή είναι ενεργοποιημένη, το Slic3r θα κεντράρει αυτόματα τα αντικείμενα γύρω από το κέντρο της πλατφόρμας εκτύπωσης.',
        default     => $Slic3r::GUI::Settings->{_}{autocenter},
    ));
    $optgroup->append_single_option_line(Slic3r::GUI::OptionsGroup::Option->new(
        opt_id      => 'background_processing',
        type        => 'bool',
        label       => 'Επεξεργασία στο παρασκήνιο',
        tooltip     => 'Αν αυτή η επιλογή είναι ενεργοποιημένη, το Slic3r θα προεπεξεργαστεί τα αντικείμενα αμέσως με την φόρτωσή τους προκειμένου να εξοικονομηθεί χρόνος κατά τη διάρκεια της εξαγωγής G-code.',
        default     => $Slic3r::GUI::Settings->{_}{background_processing},
        readonly    => !$Slic3r::have_threads,
    ));
    
    my $sizer = Wx::BoxSizer->new(wxVERTICAL);
    $sizer->Add($optgroup->sizer, 0, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 10);
    
    my $buttons = $self->CreateStdDialogButtonSizer(wxOK | wxCANCEL);
    EVT_BUTTON($self, wxID_OK, sub { $self->_accept });
    $sizer->Add($buttons, 0, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 10);
    
    $self->SetSizer($sizer);
    $sizer->SetSizeHints($self);
    
    return $self;
}

sub _accept {
    my $self = shift;
    
    if ($self->{values}{mode}) {
        Slic3r::GUI::warning_catcher($self)->("Πρέπει να επανεκκινήσετε το Slic3r για να γίνουν αποτελεσματικές οι αλλαγές.");
    }
    
    $Slic3r::GUI::Settings->{_}{$_} = $self->{values}{$_} for keys %{$self->{values}};
    wxTheApp->save_settings;
    
    $self->EndModal(wxID_OK);
    $self->Close;  # needed on Linux
}

1;
