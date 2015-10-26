#include "PrintConfig.hpp"

namespace Slic3r {

t_optiondef_map
PrintConfigDef::build_def() {
    t_optiondef_map Options;
    
    Options["avoid_crossing_perimeters"].type = coBool;
    Options["avoid_crossing_perimeters"].label = "Αποφυγή διασταύρωσης περιμέτρων";
    Options["avoid_crossing_perimeters"].tooltip = "Βελτιστοποίηση των κινήσεων ώστε να ελαχιστοποιηθεί η διασταύρωση των περιμέτρων. Αυτό είναι περισσότερο χρήσιμο με τους εξωθητήρες Bowden που στάζουν. Αυτή η λειτουργία καθυστερεί και την εκτύπωση και την δημιουργία G-code.";
    Options["avoid_crossing_perimeters"].cli = "avoid-crossing-perimeters!";

    Options["bed_shape"].type = coPoints;
    Options["bed_shape"].label = "Σχήμα Πλατφόρμας Εκτύπωσης";

    Options["bed_temperature"].type = coInt;
    Options["bed_temperature"].label = "Άλλες στρώσεις";
    Options["bed_temperature"].tooltip = "Θερμοκρασία πλατφόρμας για τις στρώσεις μετά την πρώτη. Θέστε μηδέν για να απενεργοποιήσετε τις εντολές για έλεγχο της θερμοκρασίας πλατφόρμας στην έξοδο";
    Options["bed_temperature"].cli = "bed-temperature=i";
    Options["bed_temperature"].full_label = "Θερμοκρασία Πλατφόρμας";
    Options["bed_temperature"].min = 0;
    Options["bed_temperature"].max = 300;

    Options["before_layer_gcode"].type = coString;
    Options["before_layer_gcode"].label = "G-code πριν την αλλαγή στρώσης";
    Options["before_layer_gcode"].tooltip = "Αυτός ο ειδικός κώδικας προστίθεται σε κάθε αλλαγή στρώσεων που γίνεται, αμέσως μετά την κίνηση του Z. Σημειώστε ότι μπορείτε να χρησιμοποιήσετε μεταβλητές placeholder για όλες τις ρυθμίσεις του Slic3r καθώς επίσης και [layer_num] και [layer_z].";
    Options["before_layer_gcode"].cli = "before-layer-gcode=s";
    Options["before_layer_gcode"].multiline = true;
    Options["before_layer_gcode"].full_width = true;
    Options["before_layer_gcode"].height = 50;

    Options["bottom_solid_layers"].type = coInt;
    Options["bottom_solid_layers"].label = "Κάτω";
    Options["bottom_solid_layers"].category = "Στρώσεις και Περίμετροι";
    Options["bottom_solid_layers"].tooltip = "Αριθμός συμπαγών στρώσεων για να δημιουργηθούν στις κάτω επιφάνειες";
    Options["bottom_solid_layers"].cli = "bottom-solid-layers=i";
    Options["bottom_solid_layers"].full_label = "Κατώτερες συμπαγείς στρώσεις";
    Options["bottom_solid_layers"].min = 0;

    Options["bridge_acceleration"].type = coFloat;
    Options["bridge_acceleration"].label = "Γέφυρα";
    Options["bridge_acceleration"].tooltip = "Η επιτάχυνση που θα χρησιμοποιεί ο εκτυπωτής για τις γέφυρες. Θέστε μηδέν για απενεργοποίηση του ελέγχου επιτάχυνσης των γεφυρών.";
    Options["bridge_acceleration"].sidetext = "mm/s²";
    Options["bridge_acceleration"].cli = "bridge-acceleration=f";
    Options["bridge_acceleration"].min = 0;

    Options["bridge_fan_speed"].type = coInt;
    Options["bridge_fan_speed"].label = "Ταχύτητα ανεμιστήρα γεφυρών";
    Options["bridge_fan_speed"].tooltip = "Αυτή η ταχύτητα ανεμιστήρα επιβάλλεται κατά τη διάρκεια όλων των γεφυρών και των προεξοχών";
    Options["bridge_fan_speed"].sidetext = "%";
    Options["bridge_fan_speed"].cli = "bridge-fan-speed=i";
    Options["bridge_fan_speed"].min = 0;
    Options["bridge_fan_speed"].max = 100;

    Options["bridge_flow_ratio"].type = coFloat;
    Options["bridge_flow_ratio"].label = "Αναλογία Ροής Γέφυρας";
    Options["bridge_flow_ratio"].category = "Για προχωρημένους";
    Options["bridge_flow_ratio"].tooltip = "Αυτός ο συντελεστής επηρεάζει την ποσότητα του πλαστικού για το γεφύρωμα. Μπορείτε να το μειώσετε ελαφρώς για να τραβηχθεί το εξωθούμενο υλικό και να αποφευχθεί η χαλάρωση, παρόλο που οι προκαθορισμένες ρυθμίσεις είναι συνήθως καλές και μπορείτε να πειραματιστείτε με την ψύξη του (χρησιμοποιώντας ανεμιστήρα) πριν κάνετε κάποια αλλαγή.";
    Options["bridge_flow_ratio"].cli = "bridge-flow-ratio=f";
    Options["bridge_flow_ratio"].min = 0;

    Options["bridge_speed"].type = coFloat;
    Options["bridge_speed"].label = "Γέφυρες";
    Options["bridge_speed"].category = "Ταχύτητα";
    Options["bridge_speed"].tooltip = "Ταχύτητα εκτύπωσης γεφυρών.";
    Options["bridge_speed"].sidetext = "mm/s";
    Options["bridge_speed"].cli = "bridge-speed=f";
    Options["bridge_speed"].aliases.push_back("bridge_feed_rate");
    Options["bridge_speed"].min = 0;

    Options["brim_width"].type = coFloat;
    Options["brim_width"].label = "Πλάτος χείλους";
    Options["brim_width"].tooltip = "Οριζόντιο πλάτος του χείλους που θα εκτυπωθεί γύρω από κάθε αντικείμενο στην πρώτη στρώση.";
    Options["brim_width"].sidetext = "mm";
    Options["brim_width"].cli = "brim-width=f";
    Options["brim_width"].min = 0;

    Options["complete_objects"].type = coBool;
    Options["complete_objects"].label = "Ολοκλήρωση μεμονωμένων αντικειμένων";
    Options["complete_objects"].tooltip = "Όταν εκτυπώνονται πολλαπλά αντικείμενα ή αντίγραφα, αυτή η λειτουργία θα ολοκληρώσει κάθε αντικείμενο πριν προχωρήσει στο επόμενο (και ξεκινήσει από την πιο κάτω στρώση). Αυτή η λειτουργία είναι χρήσιμη για να αποφευχθεί ο κίνδυνος κατεστραμμένων εκτυπώσεων. Το Slic3r θα σας προειδοποιεί και θα προλαμβάνει τις συγκρούσεις του εξωθητήρα, αλλά χρειάζεται προσοχή.";
    Options["complete_objects"].cli = "complete-objects!";

    Options["cooling"].type = coBool;
    Options["cooling"].label = "Ενεργοποίηση αυτόματης ψύξης";
    Options["cooling"].tooltip = "Αυτό το πεδίο ενεργοποιεί τη μέθοδο αυτόματης ψύξης που ρυθμίζει την ταχύτητα εκτύπωσης και την ταχύτητα του ανεμιστήρα σε συνάρτηση με τον χρόνο εκτύπωσης της στρώσης";
    Options["cooling"].cli = "cooling!";

    Options["default_acceleration"].type = coFloat;
    Options["default_acceleration"].label = "Προεπιλογή";
    Options["default_acceleration"].tooltip = "Αυτή είναι η επιτάχυνση στην οποία θα επανέλθει ο εκτυπωτής σας μετά τη χρήση διαφορετικών τιμών επιτάχυνσης λόγω άλλων λειτουργιών (περίμετρος/γέμισμα). Θέστε μηδέν για να αποφευχθεί η επαναφορά επιτάχυνσης.";
    Options["default_acceleration"].sidetext = "mm/s²";
    Options["default_acceleration"].cli = "default-acceleration=f";
    Options["default_acceleration"].min = 0;

    Options["disable_fan_first_layers"].type = coInt;
    Options["disable_fan_first_layers"].label = "Απενεργοποίηση ανεμιστήρα για τις πρώτες";
    Options["disable_fan_first_layers"].tooltip = "Μπορείτε να θέσετε θετική τιμή για να απενεργοποιήσετε τελείως τον ανεμιστήρα κατά τη διάρκεια εκτύπωσης των πρώτων στρώσεων, έτσι ώστε να μην επιδεινωθεί η προσκόλληση υλικού.";
    Options["disable_fan_first_layers"].sidetext = "στρώσεις";
    Options["disable_fan_first_layers"].cli = "disable-fan-first-layers=i";
    Options["disable_fan_first_layers"].min = 0;
    Options["disable_fan_first_layers"].max = 1000;

    Options["dont_support_bridges"].type = coBool;
    Options["dont_support_bridges"].label = "Μη στήριξη γεφυρών";
    Options["dont_support_bridges"].category = "Υλικό στήριξης";
    Options["dont_support_bridges"].tooltip = "Πειραματική επιλογή για την αποφυγή δημιουργίας υποστηρικτικού υλικού κάτω από γεφυρωμένες περιοχές.";
    Options["dont_support_bridges"].cli = "dont-support-bridges!";

    Options["duplicate_distance"].type = coFloat;
    Options["duplicate_distance"].label = "Απόσταση μεταξύ αντιγράφων";
    Options["duplicate_distance"].tooltip = "Η απόσταση που χρησιμοποιείται για την αυτόματη τοποθέτηση των αντικειμένων στη πλατφόρμα.";
    Options["duplicate_distance"].sidetext = "mm";
    Options["duplicate_distance"].cli = "duplicate-distance=f";
    Options["duplicate_distance"].aliases.push_back("multiply_distance");
    Options["duplicate_distance"].min = 0;

    Options["end_gcode"].type = coString;
    Options["end_gcode"].label = "G-code τερματισμού";
    Options["end_gcode"].tooltip = "Αυτή η διαδικασία τερματισμού εισάγεται στο τέλος του αρχείου εξόδου. Επισημαίνεται ότι μπορείτε να χρησιμοποιήσετε μεταβλητές για όλες τις ρυθμίσεις του Slic3r.";
    Options["end_gcode"].cli = "end-gcode=s";
    Options["end_gcode"].multiline = true;
    Options["end_gcode"].full_width = true;
    Options["end_gcode"].height = 120;

    Options["external_fill_pattern"].type = coEnum;
    Options["external_fill_pattern"].label = "Άνω/κάτω μοτίβο γεμίσματος";
    Options["external_fill_pattern"].category = "Εσωτερικό γέμισμα";
    Options["external_fill_pattern"].tooltip = "Μοτίβο γεμίσματος άνω/κάτω εσωτερικού γεμίσματος. Αυτό επηρεάζει μόνο την εξωτερική ορατή στρώση, και όχι τα γειτονικά στερεά κελιά.";
    Options["external_fill_pattern"].cli = "external-fill-pattern|solid-fill-pattern=s";
    Options["external_fill_pattern"].enum_keys_map = ConfigOptionEnum<InfillPattern>::get_enum_values();
    Options["external_fill_pattern"].enum_values.push_back("rectilinear");
    Options["external_fill_pattern"].enum_values.push_back("concentric");
    Options["external_fill_pattern"].enum_values.push_back("hilbertcurve");
    Options["external_fill_pattern"].enum_values.push_back("archimedeanchords");
    Options["external_fill_pattern"].enum_values.push_back("octagramspiral");
    Options["external_fill_pattern"].enum_labels.push_back("Rectilinear");
    Options["external_fill_pattern"].enum_labels.push_back("Concentric");
    Options["external_fill_pattern"].enum_labels.push_back("Hilbert Curve");
    Options["external_fill_pattern"].enum_labels.push_back("Archimedean Chords");
    Options["external_fill_pattern"].enum_labels.push_back("Octagram Spiral");
    Options["external_fill_pattern"].aliases.push_back("solid_fill_pattern");

    Options["external_perimeter_extrusion_width"].type = coFloatOrPercent;
    Options["external_perimeter_extrusion_width"].label = "Εξωτερικές περίμετροι";
    Options["external_perimeter_extrusion_width"].category = "Πλάτος εξώθησης";
    Options["external_perimeter_extrusion_width"].tooltip = "Θέστε εδώ μη μηδενική τιμή για να οριστεί ένα χειροκίνητο πλάτος εξώθησης για τις εξωτερικές περιμέτρους. Εάν το αφήσετε μηδέν, θα χρησιμοποιηθεί μια αυτόματη τιμή για να μεγιστοποιήσει την ακρίβεια των εξωτερικών ορατών επιφανειών. Εάν εκφραστεί σε ποσοστό (για παράδειγμα 200%) θα υπολογιστεί με βάση το ύψος της στρώσης.";
    Options["external_perimeter_extrusion_width"].sidetext = "mm or % (leave 0 for default)";
    Options["external_perimeter_extrusion_width"].cli = "external-perimeter-extrusion-width=s";

    Options["external_perimeter_speed"].type = coFloatOrPercent;
    Options["external_perimeter_speed"].label = "Εξωτερικές περίμετροι";
    Options["external_perimeter_speed"].category = "Ταχύτητα";
    Options["external_perimeter_speed"].tooltip = "Αυτή η ρύθμιση θα επηρεάσει την ταχύτητα των εξωτερικών περιμέτρων (των ορατών). Εάν εκφραστεί σε ποσοστό (για παράδειγμα: 80%) θα υπολογιστεί σύμφωνα με τη ρύθμιση της ταχύτητας εκτύπωσης των περιμέτρων που ορίζεται παραπάνω. Θέστε μηδέν για αυτόματο υπολογισμό.";
    Options["external_perimeter_speed"].sidetext = "mm/s ή %";
    Options["external_perimeter_speed"].cli = "external-perimeter-speed=s";
    Options["external_perimeter_speed"].ratio_over = "perimeter_speed";
    Options["external_perimeter_speed"].min = 0;

    Options["external_perimeters_first"].type = coBool;
    Options["external_perimeters_first"].label = "Πρώτα οι εξωτερικές περίμετροι";
    Options["external_perimeters_first"].category = "Στρώσεις και Περίμετροι";
    Options["external_perimeters_first"].tooltip = "Εκτύπωση των περιγραμμάτων των περιμέτρων από την εξωτερική προς την εσωτερική αντί για την προκαθορισμένη αντίστροφη σειρά";
    Options["external_perimeters_first"].cli = "external-perimeters-first!";

    Options["extra_perimeters"].type = coBool;
    Options["extra_perimeters"].label = "Επιπλέον περίμετροι εφόσον χρειάζονται";
    Options["extra_perimeters"].category = "Στρώσεις και Περίμετροι";
    Options["extra_perimeters"].tooltip = "Προσθήκη περισσότερων περιμέτρων όταν χρειάζονται για την αποφυγή κενών σε κεκλιμένα τοιχώματα";
    Options["extra_perimeters"].cli = "extra-perimeters!";

    Options["extruder"].type = coInt;
    Options["extruder"].gui_type = "i_enum_open";
    Options["extruder"].label = "Εξωθητήρας";
    Options["extruder"].category = "Εξωθητήρες";
    Options["extruder"].tooltip = "Εξωθητήρας για χρήση (εκτός εάν καθορίζονται πιο συγκεκριμένες ρυθμίσεις εξωθητήρα).";
    Options["extruder"].cli = "extruder=i";
    Options["extruder"].min = 0;  // 0 = inherit defaults
    Options["extruder"].enum_labels.push_back("default");  // override label for item 0
    Options["extruder"].enum_labels.push_back("1");
    Options["extruder"].enum_labels.push_back("2");
    Options["extruder"].enum_labels.push_back("3");
    Options["extruder"].enum_labels.push_back("4");

    Options["extruder_clearance_height"].type = coFloat;
    Options["extruder_clearance_height"].label = "Ύψος";
    Options["extruder_clearance_height"].tooltip = "Θέστε εδώ την κάθετη απόσταση μεταξύ της αιχμής του ακροφύσιου και (συνήθως) των Χ ράβδων μεταφοράς. Με άλλα λόγια, αυτό είναι το ύψος του κυλινδρικού διάκενου γύρω από τον εξωθητήρα, και αντιπροσωπεύει το μέγιστο βάθος που μπορεί να φτάσει πριν συγκρουστεί με άλλα εκτυπωμένα αντικείμενα.";
    Options["extruder_clearance_height"].sidetext = "mm";
    Options["extruder_clearance_height"].cli = "extruder-clearance-height=f";
    Options["extruder_clearance_height"].min = 0;

    Options["extruder_clearance_radius"].type = coFloat;
    Options["extruder_clearance_radius"].label = "Ακτίνα";
    Options["extruder_clearance_radius"].tooltip = "Θέστε εδώ την ακτίνα ανοιχτού χώρου γύρω από τον εξωθητήρα.  Εάν ο εξωθητήρας δεν είναι κεντραρισμένος, επιλέξτε την μεγαλύτερη τιμή για ασφάλεια. Αυτή η ρύθμιση χρησιμοποιείται για να ελέγχει για συγκρούσεις και για να εμφανίζει τη γραφική προεπισκόπηση στην πλατφόρμα.";
    Options["extruder_clearance_radius"].sidetext = "mm";
    Options["extruder_clearance_radius"].cli = "extruder-clearance-radius=f";
    Options["extruder_clearance_radius"].min = 0;

    Options["extruder_offset"].type = coPoints;
    Options["extruder_offset"].label = "Αντιστάθμιση εξωθητήρα";
    Options["extruder_offset"].tooltip = "Εάν το λογισμικό σας δεν μπορεί να χειριστεί την μετατόπιση του εξωθητήρα θα πρέπει να το υπολογίσει το G-code. Αυτή η επιλογή σας επιτρέπει να καθορίσετε την μετατόπιση του κάθε εξωθητήρα σε σχέση με τον αρχικό. Αναμένει θετικές συντεταγμένες (που θα πρέπει να αφαιρεθούν από τις συντεταγμένες XY).";
    Options["extruder_offset"].sidetext = "mm";
    Options["extruder_offset"].cli = "extruder-offset=s@";

    Options["extrusion_axis"].type = coString;
    Options["extrusion_axis"].label = "Άξονας εξώθησης";
    Options["extrusion_axis"].tooltip = "Χρησιμοποιήστε αυτή την επιλογή για να ορίσετε το γράμμα άξονα που θα έχει ο εξωθητήρας του εκτυπωτή σας (συνήθως χρησιμοποιείται το E αλλά κάποιοι εκτυπωτές χρησιμοποιούν το A).";
    Options["extrusion_axis"].cli = "extrusion-axis=s";

    Options["extrusion_multiplier"].type = coFloats;
    Options["extrusion_multiplier"].label = "Πολλαπλασιαστής εξώθησης";
    Options["extrusion_multiplier"].tooltip = "Αυτός ο συντελεστής αλλάζει την ποσότητα της ροής εκθετικά. Μπορεί να χρειαστεί να πειράξετε αυτή την ρύθμιση για να βελτιωθεί τελείωμα της επιφάνειας και να διορθωθεί το πλάτος των τοιχωμάτων. Συνήθως οι τιμές είναι μεταξύ 0.9 και 1.1. Εάν θεωρείτε ότι χρειάζεται να το αλλάξετε περαιτέρω, ελέγξτε την διάμετρο του νήματος και τα βήματα Ε του λογισμικού σας.";
    Options["extrusion_multiplier"].cli = "extrusion-multiplier=f@";

    Options["extrusion_width"].type = coFloatOrPercent;
    Options["extrusion_width"].label = "Προεπιλεγμένο πλάτος εξώθησης";
    Options["extrusion_width"].category = "Πλάτος Εξώθησης";
    Options["extrusion_width"].tooltip = "Θέστε εδώ μη μηδενική τιμή για να οριστεί χειροκίνητα το πλάτος εξώθησης. Εάν παραμείνει μηδέν, το Slic3r υπολογίζει ένα πλάτος αυτόματα. Εάν εκφραστεί σε ποσοστό (για παράδειγμα: 230%) θα υπολογιστεί με βάση το ύψος της στρώσης.";
    Options["extrusion_width"].sidetext = "mm ή % (αφήστε 0 για αυτόματο)";
    Options["extrusion_width"].cli = "extrusion-width=s";

    Options["fan_always_on"].type = coBool;
    Options["fan_always_on"].label = "Ανεμιστήρες πάντα σε λειτουργία";
    Options["fan_always_on"].tooltip = "Εάν είναι επιλεγμένο, ο ανεμιστήρας δεν θα απενεργοποιηθεί ποτέ και θα συνεχίζει να λειτουργεί τουλάχιστον στη χαμηλότερη ταχύτητα. Χρήσιμο για PLA, αλλά επιβλαβές για ABS.";
    Options["fan_always_on"].cli = "fan-always-on!";

    Options["fan_below_layer_time"].type = coInt;
    Options["fan_below_layer_time"].label = "Ενεργοποίηση ανεμιστήρα αν ο χρόνος εκτύπωσης της στρώσης είναι χαμηλός";
    Options["fan_below_layer_time"].tooltip = "Εάν ο χρόνος εκτύπωσης της στρώσης εκτιμάται ότι είναι κάτω από αυτό τον αριθμό δευτερολέπτων, ο ανεμιστήρας θα ενεργοποιηθεί και η ταχύτητα του θα υπολογιστεί με παρεμβολή των ελάχιστων και μέγιστων στροφών.";
    Options["fan_below_layer_time"].sidetext = "δευτερόλεπτα κατά προσέγγιση";
    Options["fan_below_layer_time"].cli = "fan-below-layer-time=i";
    Options["fan_below_layer_time"].width = 60;
    Options["fan_below_layer_time"].min = 0;
    Options["fan_below_layer_time"].max = 1000;

    Options["filament_colour"].type = coStrings;
    Options["filament_colour"].label = "Χρώμα";
    Options["filament_colour"].tooltip = "Αυτό χρησιμοποιείται μόνο στην διεπαφή του Slic3r για οπτική βοήθεια.";
    Options["filament_colour"].cli = "filament-color=s@";
    Options["filament_colour"].gui_type = "χρώμα";

    Options["filament_diameter"].type = coFloats;
    Options["filament_diameter"].label = "Διάμετρος";
    Options["filament_diameter"].tooltip = "Εισάγετε εδώ την διάμετρο του νήματος. Είναι απαραίτητο να δοθεί  αρκετά ακριβής τιμή, επομένως χρησιμοποιείστε ένα παχύμετρο και κάντε πολλαπλές μετρήσεις κατά μήκος του νήματος, στη συνέχεια υπολογίστε το μέσο όρο.";
    Options["filament_diameter"].sidetext = "mm";
    Options["filament_diameter"].cli = "filament-diameter=f@";
    Options["filament_diameter"].min = 0;

    Options["fill_angle"].type = coInt;
    Options["fill_angle"].label = "Γέμισμα γωνίας";
    Options["fill_angle"].category = "Εσωτερικό γέμισμα";
    Options["fill_angle"].tooltip = "Προεπιλεγμένη βασική γωνία για τον προσανατολισμό του εσωτερικού γεμίσματος. Σε αυτό θα εφαρμοστεί cross-hatching. Οι γέφυρες θα γεμίσουν εσωτερικά χρησιμοποιώντας την καλύτερη κατεύθυνση που θα εντοπίζει το Slic3r, οπότε αυτή η ρύθμιση δεν τις επηρεάζει.";
    Options["fill_angle"].sidetext = "°";
    Options["fill_angle"].cli = "fill-angle=i";
    Options["fill_angle"].min = 0;
    Options["fill_angle"].max = 359;

    Options["fill_density"].type = coPercent;
    Options["fill_density"].gui_type = "f_enum_open";
    Options["fill_density"].gui_flags = "show_value";
    Options["fill_density"].label = "Πυκνότητα γεμίσματος";
    Options["fill_density"].category = "Εσωτερικό γέμισμα";
    Options["fill_density"].tooltip = "Η πυκνότητα του εσωτερικού γεμίσματος. Εκφράζεται στο εύρος 0% - 100%.";
    Options["fill_density"].sidetext = "%";
    Options["fill_density"].cli = "fill-density=s";
    Options["fill_density"].min = 0;
    Options["fill_density"].max = 100;
    Options["fill_density"].enum_values.push_back("0");
    Options["fill_density"].enum_values.push_back("5");
    Options["fill_density"].enum_values.push_back("10");
    Options["fill_density"].enum_values.push_back("15");
    Options["fill_density"].enum_values.push_back("20");
    Options["fill_density"].enum_values.push_back("25");
    Options["fill_density"].enum_values.push_back("30");
    Options["fill_density"].enum_values.push_back("40");
    Options["fill_density"].enum_values.push_back("50");
    Options["fill_density"].enum_values.push_back("60");
    Options["fill_density"].enum_values.push_back("70");
    Options["fill_density"].enum_values.push_back("80");
    Options["fill_density"].enum_values.push_back("90");
    Options["fill_density"].enum_values.push_back("100");
    Options["fill_density"].enum_labels.push_back("0%");
    Options["fill_density"].enum_labels.push_back("5%");
    Options["fill_density"].enum_labels.push_back("10%");
    Options["fill_density"].enum_labels.push_back("15%");
    Options["fill_density"].enum_labels.push_back("20%");
    Options["fill_density"].enum_labels.push_back("25%");
    Options["fill_density"].enum_labels.push_back("30%");
    Options["fill_density"].enum_labels.push_back("40%");
    Options["fill_density"].enum_labels.push_back("50%");
    Options["fill_density"].enum_labels.push_back("60%");
    Options["fill_density"].enum_labels.push_back("70%");
    Options["fill_density"].enum_labels.push_back("80%");
    Options["fill_density"].enum_labels.push_back("90%");
    Options["fill_density"].enum_labels.push_back("100%");

    Options["fill_pattern"].type = coEnum;
    Options["fill_pattern"].label = "Μοτίβο γεμίσματος";
    Options["fill_pattern"].category = "Εσωτερικό γέμισμα";
    Options["fill_pattern"].tooltip = "Μοτίβο γεμίσματος για γενικό γέμισμα χαμηλής πυκνότητας.";
    Options["fill_pattern"].cli = "fill-pattern=s";
    Options["fill_pattern"].enum_keys_map = ConfigOptionEnum<InfillPattern>::get_enum_values();
    Options["fill_pattern"].enum_values.push_back("rectilinear");
    Options["fill_pattern"].enum_values.push_back("line");
    Options["fill_pattern"].enum_values.push_back("concentric");
    Options["fill_pattern"].enum_values.push_back("honeycomb");
    Options["fill_pattern"].enum_values.push_back("3dhoneycomb");
    Options["fill_pattern"].enum_values.push_back("hilbertcurve");
    Options["fill_pattern"].enum_values.push_back("archimedeanchords");
    Options["fill_pattern"].enum_values.push_back("octagramspiral");
    Options["fill_pattern"].enum_labels.push_back("Ευθύγραμμο");
    Options["fill_pattern"].enum_labels.push_back("Γραμμή");
    Options["fill_pattern"].enum_labels.push_back("Ομοκεντρικό");
    Options["fill_pattern"].enum_labels.push_back("Κόμβος κυψέλης");
    Options["fill_pattern"].enum_labels.push_back("Τρισδιάστατος Κόμβος Κυψέλης");
    Options["fill_pattern"].enum_labels.push_back("Καμπύλη του Χίλμπερτ");
    Options["fill_pattern"].enum_labels.push_back("Αρχιμήδειες Χορδές");
    Options["fill_pattern"].enum_labels.push_back("Οκταγραμμικό Σπιράλ");

    Options["first_layer_acceleration"].type = coFloat;
    Options["first_layer_acceleration"].label = "Πρώτη στρώση";
    Options["first_layer_acceleration"].tooltip = "Αυτή είναι η επιτάχυνση που χρησιμοποιεί ο εκτυπωτής σας για την πρώτη στρώση. Θέστε μηδέν για να απενεργοποιηθεί ο έλεγχος της επιτάχυνσης για την πρώτη στρώση.";
    Options["first_layer_acceleration"].sidetext = "mm/s²";
    Options["first_layer_acceleration"].cli = "first-layer-acceleration=f";
    Options["first_layer_acceleration"].min = 0;

    Options["first_layer_bed_temperature"].type = coInt;
    Options["first_layer_bed_temperature"].label = "Πρώτη στρώση";
    Options["first_layer_bed_temperature"].tooltip = "Θερμοκρασία της πλάκας κατασκευής για την πρώτη στρώση. Θέστε μηδέν για να απενεργοποιηθούν οι εντολές ελέγχου της θερμοκρασίας της πλατφόρμας.";
    Options["first_layer_bed_temperature"].cli = "first-layer-bed-temperature=i";
    Options["first_layer_bed_temperature"].max = 0;
    Options["first_layer_bed_temperature"].max = 300;

    Options["first_layer_extrusion_width"].type = coFloatOrPercent;
    Options["first_layer_extrusion_width"].label = "Πρώτη στρώση";
    Options["first_layer_extrusion_width"].tooltip = "Θέστε μη μηδενική τιμή για να ορίσετε χειροκίνητα το πλάτος του εξωθητήρα για την πρώτη στρώση. Μπορείτε να το χρησιμοποιήσετε αυτό για να αναγκαστεί το υλικό να έχει μεγαλύτερο πάχος για καλύτερη προσκόλληση. Εάν εκφράζεται σε ποσοστό (για παράδειγμα 120%) θα υπολογιστεί πάνω από το ύψος της πρώτης στρώσης. Εάν θέσετε τιμή μηδέν, θα χρησιμοποιήσει το προκαθορισμένο πλάτος εξώθησης.";
    Options["first_layer_extrusion_width"].sidetext = "mm ή % (αφήστε 0 για προκαθορισμένο)";
    Options["first_layer_extrusion_width"].cli = "first-layer-extrusion-width=s";
    Options["first_layer_extrusion_width"].ratio_over = "first_layer_height";

    Options["first_layer_height"].type = coFloatOrPercent;
    Options["first_layer_height"].label = "Ύψος πρώτης στρώσης";
    Options["first_layer_height"].category = "Στρώσεις και Περίμετροι";
    Options["first_layer_height"].tooltip = "Όταν εκτυπώνετε σε πολύ χαμηλό ύψος στρώσης, ίσως να επιθυμείτε ακόμα να εκτυπώσετε μια παχύτερη κατώτερη στρώση για να βελτιώσετε την προσκόλληση και την ανοχή στις όχι τέλεια κατασκευασμένες πλατφόρμες. Αυτό μπορεί να εκφραστεί σαν μια απόλυτη τιμή ή σε ποσοστό (για παράδειγμα: 150%) με βάση το προκαθορισμένο ύψος στρώσης.";
    Options["first_layer_height"].sidetext = "mm ή %";
    Options["first_layer_height"].cli = "first-layer-height=s";
    Options["first_layer_height"].ratio_over = "layer_height";

    Options["first_layer_speed"].type = coFloatOrPercent;
    Options["first_layer_speed"].label = "Ταχύτητα πρώτης στρώσης";
    Options["first_layer_speed"].tooltip = "Εάν εκφράζεται ως απόλυτη τιμή σε mm/s, αυτή η ταχύτητα θα εφαρμοστεί σε όλες τις κινήσεις του εκτυπωτή για την πρώτη στρώση, ανεξάρτητα από τον τύπο τους. Εάν εκφράζεται ως ποσοστό (για παράδειγμα: 40%), θα αλλάξει την κλίμακα στις προεπιλεγμένες ταχύτητες.";
    Options["first_layer_speed"].sidetext = "mm/s ή %";
    Options["first_layer_speed"].cli = "first-layer-speed=s";
    Options["first_layer_speed"].min = 0;

    Options["first_layer_temperature"].type = coInts;
    Options["first_layer_temperature"].label = "Πρώτη στρώση";
    Options["first_layer_temperature"].tooltip = "Θερμοκρασία εξωθητήρα για την πρώτη στρώση. Εάν θέλετε να ελέγχετε την θερμοκρασία χειροκίνητα κατα τη διάρκεια της εκτύπωσης, θέστε σε αυτό τιμή μηδέν για να απενεργοποιηθούν οι εντολές ελέγχου της θερμοκρασίας για το αρχείο εξόδου.";
    Options["first_layer_temperature"].cli = "first-layer-temperature=i@";
    Options["first_layer_temperature"].min = 0;
    Options["first_layer_temperature"].max = 400;

    Options["gap_fill_speed"].type = coFloat;
    Options["gap_fill_speed"].label = "Γέμισμα κενού";
    Options["gap_fill_speed"].category = "Ταχύτητα";
    Options["gap_fill_speed"].tooltip = "Ταχύτητα γεμίσματος μικρών κενών χρησιμοποιώντας σύντομες κινήσεις ζιγκ-ζαγκ. Διατηρείστε τη σε λογικά χαμηλή τιμή για να αποφύγετε υπερβολικά τραντάγματα και προβλήματα συντονισμού. Θέστε μηδέν για απενεργοποίηση του γεμίσματος κενού.";
    Options["gap_fill_speed"].sidetext = "mm/s";
    Options["gap_fill_speed"].cli = "gap-fill-speed=f";
    Options["gap_fill_speed"].min = 0;

    Options["gcode_arcs"].type = coBool;
    Options["gcode_arcs"].label = "Χρήση ατόφιου τόξου G-code";
    Options["gcode_arcs"].tooltip = "Αυτή η πειραματική λειτουργία προσπαθεί να ανιχνεύσει τόξα από τα τμήματα και να παράγει εντολές τόξων G2/G3, αντί για εντολές G1 πολλαπλών ευθειών.";
    Options["gcode_arcs"].cli = "gcode-arcs!";

    Options["gcode_comments"].type = coBool;
    Options["gcode_comments"].label = "Λεπτομερές G-code";
    Options["gcode_comments"].tooltip = "Ενεργοποιήστε αυτή τη λειτουργία για να πάρετε ένα αρχείο G-code με σχόλια, στο οποίο κάθε γραμμή θα εξηγείται από ένα κείμενο. Εάν η εκτύπωση γίνεται από κάρτα SD, το επιπλέον μέγεθος του αρχείου θα καθυστερεί το firmware.";
    Options["gcode_comments"].cli = "gcode-comments!";

    Options["gcode_flavor"].type = coEnum;
    Options["gcode_flavor"].label = "G-code μορφές";
    Options["gcode_flavor"].tooltip = "Μερικές εντολές G/Μ-code, συμπεριλαμβανομένου του ελέγχου της θερμοκρασίας και άλλων, δεν είναι γενικής χρήσης. Θέστε αυτή την επιλογή στο firmware του εκτυπωτή σας για να πάρετε μία συμβατή έξοδο. Η επιλογή \"Μη εξώθηση\" εμποδίζει το Slic3r από το να εξάγει οποιαδήποτε τιμή εξώθησης.";
    Options["gcode_flavor"].cli = "gcode-flavor=s";
    Options["gcode_flavor"].enum_keys_map = ConfigOptionEnum<GCodeFlavor>::get_enum_values();
    Options["gcode_flavor"].enum_values.push_back("reprap");
    Options["gcode_flavor"].enum_values.push_back("teacup");
    Options["gcode_flavor"].enum_values.push_back("makerware");
    Options["gcode_flavor"].enum_values.push_back("sailfish");
    Options["gcode_flavor"].enum_values.push_back("mach3");
    Options["gcode_flavor"].enum_values.push_back("machinekit");
    Options["gcode_flavor"].enum_values.push_back("no-extrusion");
    Options["gcode_flavor"].enum_labels.push_back("RepRap (Marlin/Sprinter/Repetier)");
    Options["gcode_flavor"].enum_labels.push_back("Teacup");
    Options["gcode_flavor"].enum_labels.push_back("MakerWare (MakerBot)");
    Options["gcode_flavor"].enum_labels.push_back("Sailfish (MakerBot)");
    Options["gcode_flavor"].enum_labels.push_back("Mach3/LinuxCNC");
    Options["gcode_flavor"].enum_labels.push_back("Machinekit");
    Options["gcode_flavor"].enum_labels.push_back("Μη εξώθηση");

    Options["infill_acceleration"].type = coFloat;
    Options["infill_acceleration"].label = "Εσωτερικό γέμισμα";
    Options["infill_acceleration"].tooltip = "Η επιτάχυνση που χρησιμοποιεί ο εκτυπωτής σας για το γέμισμα. Θέστε μηδέν για να απενεργοποιήσετε τον έλεγχο της επιτάχυνσης για το γέμισμα.";
    Options["infill_acceleration"].sidetext = "mm/s²";
    Options["infill_acceleration"].cli = "infill-acceleration=f";
    Options["infill_acceleration"].min = 0;

    Options["infill_every_layers"].type = coInt;
    Options["infill_every_layers"].label = "Συνδυασμός εσωτερικού γεμίσματος για κάθε";
    Options["infill_every_layers"].category = "Εσωτερικό γέμισμα";
    Options["infill_every_layers"].tooltip = "Αυτή η λειτουργία επιτρέπει τον συνδυασμό εσωτερικού γεμίσματος και αύξησης της ταχύτητας εκτύπωσης κάνοντας παχύτερες τις στρώσεις κατά το γέμισμα διατηρώντας παράλληλα την περίμετρο λεπτή.";
    Options["infill_every_layers"].sidetext = "στρώσεις";
    Options["infill_every_layers"].cli = "infill-every-layers=i";
    Options["infill_every_layers"].full_label = "Συνδυασμός εσωτερικού γεμίσματος για κάθε Ν στρώσεις.";
    Options["infill_every_layers"].min = 1;

    Options["infill_extruder"].type = coInt;
    Options["infill_extruder"].label = "Εξωθητήρας εσωτερικού γεμίσματος";
    Options["infill_extruder"].category = "Εξωθητήρες";
    Options["infill_extruder"].tooltip = "Ο εξωθητήρας που χρησιμοποιείται όταν γίνεται εσωτερικό γέμισμα.";
    Options["infill_extruder"].cli = "infill-extruder=i";
    Options["infill_extruder"].min = 1;

    Options["infill_extrusion_width"].type = coFloatOrPercent;
    Options["infill_extrusion_width"].label = "Εσωτερικό γέμισμα";
    Options["infill_extrusion_width"].category = "Πλάτος εξώθησης";
    Options["infill_extrusion_width"].tooltip = "Θέστε μη μηδενική τιμή για χειροκίνητη τιμή πλάτους εξώθησης για το εσωτερικό γέμισμα. Ίσως να θέλετε να χρησιμοποιήσετε παχύτερα υλικά εξώθησης για να γίνει το γέμισμα πιο γρήγορα και να γίνουν τα κομμάτια πιο γερά. Εάν εκφράζεται σε ποσοστό (για παράδειγμα: 90%) θα υπολογιστεί με βάση το ύψος της στρώσης.";
    Options["infill_extrusion_width"].sidetext = "mm ή % (αφήστε 0 για το προεπιλεγμένο)";
    Options["infill_extrusion_width"].cli = "infill-extrusion-width=s";

    Options["infill_first"].type = coBool;
    Options["infill_first"].label = "Γέμισμα πριν τις περιμέτρων";
    Options["infill_first"].tooltip = "This option will switch the print order of perimeters and infill, making the latter first.";
    Options["infill_first"].cli = "infill-first!";

    Options["infill_only_where_needed"].type = coBool;
    Options["infill_only_where_needed"].label = "Εσωτερικό γέμισμα όπου χρειάζεται";
    Options["infill_only_where_needed"].category = "Εσωτερικό γέμισμα";
    Options["infill_only_where_needed"].tooltip = "Αυτή η επιλογή θα αλλάξει την σειρά εκτύπωσης ανάμεσα στις περιμέτρους και το γέμισμα, δίνοντας προτεραιότητα σε όποιο είναι τελευταίο.";
    Options["infill_only_where_needed"].cli = "infill-only-where-needed!";

    Options["infill_overlap"].type = coFloatOrPercent;
    Options["infill_overlap"].label = "Εσωτερικό γέμισμα/επικάλυψη περιμέτρων";
    Options["infill_overlap"].category = "Για προχωρημένους";
    Options["infill_overlap"].tooltip = "Αυτή η ρύθμιση εφαρμόζει μία επιπλέον επικάλυψη μεταξύ του γεμίσματος και των περιμέτρων για καλύτερη σύνδεση. Θεωρητικά αυτή η ρύθμιση δεν είναι απαραίτητη, αλλά η παλινδρόμιση μπορεί να προκαλέσει κενά. Εάν εκφράζεται σε ποσοστό (παράδειγμα:15%) θα υπολογιστεί με βάση το πλάτος της περιμέτρου εξώθησης.";
    Options["infill_overlap"].sidetext = "mm ή %";
    Options["infill_overlap"].cli = "infill-overlap=s";
    Options["infill_overlap"].ratio_over = "perimeter_extrusion_width";

    Options["infill_speed"].type = coFloat;
    Options["infill_speed"].label = "Εσωτερικό γέμισμα";
    Options["infill_speed"].category = "Ταχύτητα";
    Options["infill_speed"].tooltip = "Ταχύτητα εκτύπωσης γεμίσματος εσωτερικά. Θέστε μηδέν για αυτόματο.";
    Options["infill_speed"].sidetext = "mm/s";
    Options["infill_speed"].cli = "infill-speed=f";
    Options["infill_speed"].aliases.push_back("print_feed_rate");
    Options["infill_speed"].aliases.push_back("infill_feed_rate");
    Options["infill_speed"].min = 0;

    Options["interface_shells"].type = coBool;
    Options["interface_shells"].label = "Διασύνδεση κελιών";
    Options["interface_shells"].tooltip = "Επιβάλλει την δημιουργία στερεών κελιών μεταξύ γειτονικών υλικών/τομών. Χρήσιμο για εκτυπωτές πολλαπλών εξωθητήρων με ημιδιαφανή υλικά ή χειροκίνητα αποσπώμενα υλικά στίριξης.";
    Options["interface_shells"].cli = "interface-shells!";
    Options["interface_shells"].category = "Στρώσεις και Περίμετροι";

    Options["layer_gcode"].type = coString;
    Options["layer_gcode"].label = "G-code μετά την αλλαγή στρώσης";
    Options["layer_gcode"].tooltip = "Αυτό το κομμάτι προσαρμοσμένου κώδικα προστίθεται σε κάθε αλλαγή στρώσης, αμέσως μετά την Ζ κίνηση και πριν o εξωθητήρας μεταφερθεί στο αρχικό σημείο της πρώτης στρώσης. Σημειώστε οτί μπορείτε να χρησιμοποιήσετε μεταβλητές για όλες τις ρυθμίσεις του Slic3r καθώς επίσης και τα [layer_num] και [layer_z].";
    Options["layer_gcode"].cli = "after-layer-gcode|layer-gcode=s";
    Options["layer_gcode"].multiline = true;
    Options["layer_gcode"].full_width = true;
    Options["layer_gcode"].height = 50;

    Options["layer_height"].type = coFloat;
    Options["layer_height"].label = "Ύψος Στρώσης";
    Options["layer_height"].category = "Στρώσεις και Περίμετροι";
    Options["layer_height"].tooltip = "Αυτή η ρύθμιση ελέγχει το ύψος (οπότε και τον συνολικό αριθμό) των slice/στρώσεων. Η λεπτότερες στρώσεις δίνουν καλύτερη ακρίβεια αλλά θέλει περισσότερο χρόνο για να εκτυπωθούν.";
    Options["layer_height"].sidetext = "mm";
    Options["layer_height"].cli = "layer-height=f";
    Options["layer_height"].min = 0;

    Options["max_fan_speed"].type = coInt;
    Options["max_fan_speed"].label = "Μέγιστο";
    Options["max_fan_speed"].tooltip = "Αυτή η ρύθμιση αντιπροσωπεύει την μέγιστη ταχύτητα του ανεμιστήρα.";
    Options["max_fan_speed"].sidetext = "%";
    Options["max_fan_speed"].cli = "max-fan-speed=i";
    Options["max_fan_speed"].min = 0;
    Options["max_fan_speed"].max = 100;

    Options["min_fan_speed"].type = coInt;
    Options["min_fan_speed"].label = "Ελάχιστο";
    Options["min_fan_speed"].tooltip = "Αυτή η ρύθμιση αντιπροσωπεύει το ελάχιστο PWM που χρειάζεται ο ανεμιστήρας για να λειτουργήσει.";
    Options["min_fan_speed"].sidetext = "%";
    Options["min_fan_speed"].cli = "min-fan-speed=i";
    Options["min_fan_speed"].min = 0;
    Options["min_fan_speed"].max = 100;

    Options["min_print_speed"].type = coInt;
    Options["min_print_speed"].label = "Ελάχιστη ταχύτητα εκτύπωσης";
    Options["min_print_speed"].tooltip = "Το Slic3r δεν θα χαμηλώσει την ταχύτητα κάτω από αυτή την τιμή.";
    Options["min_print_speed"].sidetext = "mm/s";
    Options["min_print_speed"].cli = "min-print-speed=f";
    Options["min_print_speed"].min = 0;

    Options["max_print_speed"].type = coFloat;
    Options["max_print_speed"].label = "Μέγιστη ταχύτητα εκτύπωσης";
    Options["max_print_speed"].tooltip = "Όταν οι υπόλοιπες ταχύτητες έχουν ρυθμιστεί σε τιμή μηδέν το Slic3r θα υπολογίσει αυτόματα την βέλτιστη ταχύτητα με σκοπό να διατηρήσει σταθερή την πίεση που ασκεί ο εξωθητήρας. Αυτή η πειραματική ρύθμιση χρησιμοποιείται για να θέσετε την μέγιστη ταχύτητα που επιτρέπετε να έχει ο εκτυπωτής.";
    Options["max_print_speed"].sidetext = "mm/s";
    Options["max_print_speed"].cli = "max-print-speed=f";
    Options["max_print_speed"].min = 1;

    Options["max_volumetric_speed"].type = coFloat;
    Options["max_volumetric_speed"].label = "Μέγιστη ογκομετρική ταχύτητα";
    Options["max_volumetric_speed"].tooltip = "Αυτή η πειραματική ρύθμιση χρησιμοποιείται για να θέσετε την μέγιστη ογκομετρική ταχύτητα που υποστηρίζει εξωθητήρας.";
    Options["max_volumetric_speed"].sidetext = "mm³/s";
    Options["max_volumetric_speed"].cli = "max-volumetric-speed=f";
    Options["max_volumetric_speed"].min = 0;

    Options["min_skirt_length"].type = coFloat;
    Options["min_skirt_length"].label = "Ελάχιστο μήκος εξώθησης";
    Options["min_skirt_length"].tooltip = "Να δημιουργηθούν αρκετοί κύκλοι στο skirt ώστε να καταναλωθεί το ποσό υλικού που θέσατε. Για εκτυπωτές με πολλούς εξωθητήρες, αυτό το ελάχιστο ισχύει για όλους τους εξωθητήρες.";
    Options["min_skirt_length"].sidetext = "mm";
    Options["min_skirt_length"].cli = "min-skirt-length=f";
    Options["min_skirt_length"].min = 0;

    Options["notes"].type = coString;
    Options["notes"].label = "Σημειώσεις ρυθμίσεων παραμέτρων";
    Options["notes"].tooltip = "Μπορείτε να γράψετε εδώ τις προσωπικές σας σημειώσεις. Το κείμενο αυτό θα προστεθεί στα σχόλια της επικεφαλίδας του G-code.";
    Options["notes"].cli = "notes=s";
    Options["notes"].multiline = true;
    Options["notes"].full_width = true;
    Options["notes"].height = 130;

    Options["nozzle_diameter"].type = coFloats;
    Options["nozzle_diameter"].label = "Διάμετρος ακροφυσίων";
    Options["nozzle_diameter"].tooltip = "Αυτή είναι η διάμετρος του ακροφύσιου του εξωθητήρα (για παράδειγμα: 0.5, 0.35 κτλ.)";
    Options["nozzle_diameter"].sidetext = "mm";
    Options["nozzle_diameter"].cli = "nozzle-diameter=f@";

    Options["octoprint_apikey"].type = coString;
    Options["octoprint_apikey"].label = "Κλειδί API";
    Options["octoprint_apikey"].tooltip = "Το Slic3r μπορεί να ανεβάσει τα G-code αρχεία στο OctoPrint. Αυτό το πεδίο θα πρέπει να εμπεριέχει το API κλειδί που απαιτείται για ταυτοποίηση";
    Options["octoprint_apikey"].cli = "octoprint-apikey=s";

    Options["octoprint_host"].type = coString;
    Options["octoprint_host"].label = "Host ή IP";
    Options["octoprint_host"].tooltip = "Το Slic3r μπορεί να ανεβάσει τα G-code αρχεία στο OctoPrint. Αυτό το πεδίο θα πρέπει να εμπεριέχει το όνομα του Host ή τη διεύθυνση IP του OctoPrint.";
    Options["octoprint_host"].cli = "octoprint-host=s";

    Options["only_retract_when_crossing_perimeters"].type = coBool;
    Options["only_retract_when_crossing_perimeters"].label = "Ανασήκωση μόνο όταν διασταυρώνονται οι περίμετροι";
    Options["only_retract_when_crossing_perimeters"].tooltip = "Απενεργοποιεί την ανασήκωση όταν η διαδρομή δεν ξεπερνάει την περίμετρο της άνω στρώσης (οπότε έτσι οποιοδήποτε στάξιμο ενδέχεται να είναι αόρατο)";
    Options["only_retract_when_crossing_perimeters"].cli = "only-retract-when-crossing-perimeters!";

    Options["ooze_prevention"].type = coBool;
    Options["ooze_prevention"].label = "Ενεργοποίηση";
    Options["ooze_prevention"].tooltip = "Αυτή η επιλογή θα ρίξει την θερμοκρασία των ανενεργών εξωθητήρων ώστε να αποτραπεί το στάξιμο. Θα ενεργοποιήσει αυτόματα μία ψηλή προέκταση βάσης και θα μετακινήσει τους εξωθητήρες έξω από αυτή την περιμετρική βάση όταν αλλάζουν θερμοκρασία.";
    Options["ooze_prevention"].cli = "ooze-prevention!";

    Options["output_filename_format"].type = coString;
    Options["output_filename_format"].label = "Μορφή ονόματος αρχείου εξόδου";
    Options["output_filename_format"].tooltip = "Μπορείτε να χρησιμοποιήσετε όλες τις ρυθμίσεις παραμέτρων σαν μεταβλητές μέσα σε αυτό το πρότυπο. Για παράδειγμα: [layer_height], [fill_density] etc. You can also use [timestamp], [year], [month], [day], [hour], [minute], [second], [version], [input_filename], [input_filename_base].";
    Options["output_filename_format"].cli = "output-filename-format=s";
    Options["output_filename_format"].full_width = true;

    Options["overhangs"].type = coBool;
    Options["overhangs"].label = "Εντοπισμός γεφύρωσης περιμέτρων";
    Options["overhangs"].category = "Στρώσεις και Περίμετροι";
    Options["overhangs"].tooltip = "Πειραματική επιλογή για να ρυθμιστεί η ροή υλικού για τις προεξοχές (θα χρησιμοποιηθεί η ροή για τις γέφυρες), για να εφαρμοστεί η ταχύτητα των γεφυρών και να ενεργοποιηθεί ο ανεμιστήρας.";
    Options["overhangs"].cli = "overhangs!";

    Options["perimeter_acceleration"].type = coFloat;
    Options["perimeter_acceleration"].label = "Περίμετροι";
    Options["perimeter_acceleration"].tooltip = "Αυτή είναι η επιτάχυνση που χρησιμοποιεί ο εκτυπωτής σας για τις περιμέτρους. Μία μεγάλη τιμή όπως 9000 συνήθως δίνει καλά αποτελέσματα εάν η συσκευή σας είναι φτιαγμένο για τέτοια χρήση. Θέστε μηδέν για απενεργοποίηση του ελέγχου της επιτάχυνσης για τις περιμέτρους.";
    Options["perimeter_acceleration"].sidetext = "mm/s²";
    Options["perimeter_acceleration"].cli = "perimeter-acceleration=f";

    Options["perimeter_extruder"].type = coInt;
    Options["perimeter_extruder"].label = "Εξωθητήρας περιμέτρων";
    Options["perimeter_extruder"].category = "Εξωθητήρες";
    Options["perimeter_extruder"].tooltip = "Ο εξωθητήρας που χρησιμοποιείται όταν εκτυπώνονται οι περίμετροι και το χείλος. Ο πρώτος εξωθητήρας είναι ο 1.";
    Options["perimeter_extruder"].cli = "perimeter-extruder=i";
    Options["perimeter_extruder"].aliases.push_back("perimeters_extruder");
    Options["perimeter_extruder"].min = 1;

    Options["perimeter_extrusion_width"].type = coFloatOrPercent;
    Options["perimeter_extrusion_width"].label = "Περίμετροι";
    Options["perimeter_extrusion_width"].category = "Πλάτος εξώθησης";
    Options["perimeter_extrusion_width"].tooltip = "Εδώ μπορείτε να θέσετε μη μηδενική τιμή για να ορίσετε το πλάτος για τις περιμέτρους χειροκίνητα. Ίσως επιθυμείτε να χρησιμοποιήσετε λεπτότερη εξώθηση για να πάρετε μία πιο ακριβής επιφάνεια. Εάν εκφράζεται σε ποσοστό (για παράδειγμα: 200%) θα υπολογιστεί με βάση το ύψος της στρώσης.";
    Options["perimeter_extrusion_width"].sidetext = "mm ή % (αφήστε 0 για προεπιλεγμένο)";
    Options["perimeter_extrusion_width"].cli = "perimeter-extrusion-width=s";
    Options["perimeter_extrusion_width"].aliases.push_back("perimeters_extrusion_width");

    Options["perimeter_speed"].type = coFloat;
    Options["perimeter_speed"].label = "Περίμετροι";
    Options["perimeter_speed"].category = "Ταχύτητα";
    Options["perimeter_speed"].tooltip = "Ταχύτητα για τις περιμέτρους (περιγράμματα, γνωστά και ως κάθετα κελιά). Θέστε μηδέν για αυτόματο.";
    Options["perimeter_speed"].sidetext = "mm/s";
    Options["perimeter_speed"].cli = "perimeter-speed=f";
    Options["perimeter_speed"].aliases.push_back("perimeter_feed_rate");
    Options["perimeter_speed"].min = 0;

    Options["perimeters"].type = coInt;
    Options["perimeters"].label = "Περίμετροι";
    Options["perimeters"].category = "Στρώσεις και Περίμετροι";
    Options["perimeters"].tooltip = "Αυτή η επιλογή θέτει τον αριθμό των περιμέτρων που θα δημιουργηθούν σε κάθε στρώση. Σημειώστε ότι το Slic3r μπορεί να αυξήσει αυτόματα των αριθμό όταν εντοπίσει κεκλιμένες επιφάνειες οι οποίες ωφελούνται από τον μεγάλο αριθμό περιμέτρων εάν η επιλογή Έξτρα Περίμετροι είναι ενεργοποιημένη.";
    Options["perimeters"].sidetext = "(minimum)";
    Options["perimeters"].cli = "perimeters=i";
    Options["perimeters"].aliases.push_back("perimeter_offsets");
    Options["perimeters"].min = 0;

    Options["post_process"].type = coStrings;
    Options["post_process"].label = "Scripts προ-διεργασίας";
    Options["post_process"].tooltip = "Εάν θέλετε να επεξεργαστείτε το εξαγόμενο G-code μέσω προσαρμοσμένων scripts, δώστε εδώ τα απόλυτα μονοπάτια τους. Διαχωρίστε πολλαπλά scripts με ένα ερωτηματικό (;). Τα scripts θα περάσουν το απόλυτο μονοπάτι στο G-code αρχείο ως αρχικό όρισμα, και θα έχουν πρόσβαση στις ρυθμίσεις διαμόρφωσης του Slic3r διαβάζοντας τις μεταβλητές περιβάλλοντος.";
    Options["post_process"].cli = "post-process=s@";
    Options["post_process"].gui_flags = "serialized";
    Options["post_process"].multiline = true;
    Options["post_process"].full_width = true;
    Options["post_process"].height = 60;

    Options["pressure_advance"].type = coFloat;
    Options["pressure_advance"].label = "Προπορεία πίεση";
    Options["pressure_advance"].tooltip = "Όταν οριστεί μία μη μηδενική τιμή, αυτή η πειραματική επιλογή επιτρέπει τη ρύθμιση της πίεσης. Είναι η σταθερά Κ του αλγόριθμου προπορείας που ωθεί περισσότερο ή λιγότερο νήμα κατά τις αλλαγές της ταχύτητας. Αυτό είναι χρήσιμο για τους Bowden-tube εξωθητήρες. Λογικές τιμές είναι στο εύρος 0-10.";
    Options["pressure_advance"].cli = "pressure-advance=f";
    Options["pressure_advance"].min = 0;

    Options["raft_layers"].type = coInt;
    Options["raft_layers"].label = "Στρώσεις σχεδίας";
    Options["raft_layers"].category = "Υλικό στήριξης";
    Options["raft_layers"].tooltip = "Το αντικείμενο θα ανασηκωθεί κατά αυτόν τον αριθμό των στρώσεων, και το υλικό στήριξης θα δημιουργηθεί κάτω από αυτό.";
    Options["raft_layers"].sidetext = "στρώσεις";
    Options["raft_layers"].cli = "raft-layers=i";
    Options["raft_layers"].min = 0;

    Options["resolution"].type = coFloat;
    Options["resolution"].label = "Ανάλυση";
    Options["resolution"].tooltip = "Ελάχιστη ανάλυση λεπτομέρειας, χρησιμοποιείται για την απλοποίηση του αρχείου εισόδου προκειμένου να αυξήσει την ταχύτητα της εργασίας τεμαχισμού και να μειώσει την χρήση μνήμης. Τα μοντέλα υψηλής ανάλυσης συχνά έχουν περισσότερη λεπτομέρεια από ότι μπορούν να παρέχουν οι εκτυπωτές. Θέστε μηδέν για απενεργοποίηση οποιασδήποτε απλοποίησης και χρήση πλήρης ανάλυσης εισόδου.";
    Options["resolution"].sidetext = "mm";
    Options["resolution"].cli = "resolution=f";
    Options["resolution"].min = 0;

    Options["retract_before_travel"].type = coFloats;
    Options["retract_before_travel"].label = "Ελάχιστη μετακίνηση μετά την ανάκληση";
    Options["retract_before_travel"].tooltip = "Η ανάκληση δεν ενεργοποιείται όταν οι κινήσεις είναι μικρότερες από αυτό το μήκος.";
    Options["retract_before_travel"].sidetext = "mm";
    Options["retract_before_travel"].cli = "retract-before-travel=f@";

    Options["retract_layer_change"].type = coBools;
    Options["retract_layer_change"].label = "Ανάκληση σε αλλαγή στρώσης";
    Options["retract_layer_change"].tooltip = "Αυτό το πεδίο επιβάλλει την ανάκληση όποτε έχει γίνει μια Z κίνηση.";
    Options["retract_layer_change"].cli = "retract-layer-change!";

    Options["retract_length"].type = coFloats;
    Options["retract_length"].label = "Μήκος";
    Options["retract_length"].full_label = "Μήκος ανάκλησης";
    Options["retract_length"].tooltip = "Όταν η ανάκληση ενεργοποιηθεί, το νήμα τραβιέται πίσω σύμφωνα με τη καθορισμένη ποσότητα (το μήκος μετριέται με βάση το αρχικό νήμα, πριν εισαχθεί στον εξωθητήρα).";
    Options["retract_length"].sidetext = "mm (μηδέν για απενεργοποίηση)";
    Options["retract_length"].cli = "retract-length=f@";

    Options["retract_length_toolchange"].type = coFloats;
    Options["retract_length_toolchange"].label = "Μήκος";
    Options["retract_length_toolchange"].full_label = "Μήκος ανάκλησης (Αλλαγή εργαλείου)";
    Options["retract_length_toolchange"].tooltip = "Όταν η ανάκληση ενεργοποιηθεί πριν γίνει αλλαγή εργαλείου, το νήμα τραβιέται πίσω σύμφωνα με τη καθορισμένη ποσότητα (το μήκος μετριέται με βάση το αρχικό νήμα, πριν τοποθετηθεί στον εξωθητήρα).";
    Options["retract_length_toolchange"].sidetext = "mm (μηδέν για απενεργοποίηση)";
    Options["retract_length_toolchange"].cli = "retract-length-toolchange=f@";

    Options["retract_lift"].type = coFloats;
    Options["retract_lift"].label = "Ανασήκωμα Z";
    Options["retract_lift"].tooltip = "Εάν δώσετε θετική τιμή, ο Z θα ανυψώνεται γρήγορα κάθε φορά που ενεργοποιείται μία ανάκληση. Όταν χρησιμοποιούνται πολλοί εξωθητήρες, μόνο η ρύθμιση για τον πρώτο εξωθητήρα θα ληφθεί υπόψιν.";
    Options["retract_lift"].sidetext = "mm";
    Options["retract_lift"].cli = "retract-lift=f@";

    Options["retract_restart_extra"].type = coFloats;
    Options["retract_restart_extra"].label = "Έξτρα μήκος κατά την επανεκκίνηση";
    Options["retract_restart_extra"].tooltip = "Όταν η ανάκληση αντισταθμίζεται μετά από μία κίνηση, ο εξωθητήρας θα ωθήσει αυτό το επιπρόσθετο ποσό νήματος. Αυτή η ρύθμιση σπάνια χρειάζεται.";
    Options["retract_restart_extra"].sidetext = "mm";
    Options["retract_restart_extra"].cli = "retract-restart-extra=f@";

    Options["retract_restart_extra_toolchange"].type = coFloats;
    Options["retract_restart_extra_toolchange"].label = "Έξτρα μήκος κατά την επανέναρξη";
    Options["retract_restart_extra_toolchange"].tooltip = "Όταν η ανάκληση αντισταθμίζεται μετά από αλλαγή εργαλείου, ο εξωθητήρας θα ωθήσει αυτό το επιπρόσθετο ποσό νήματος.";
    Options["retract_restart_extra_toolchange"].sidetext = "mm";
    Options["retract_restart_extra_toolchange"].cli = "retract-restart-extra-toolchange=f@";

    Options["retract_speed"].type = coInts;
    Options["retract_speed"].label = "Ταχύτητα";
    Options["retract_speed"].full_label = "Ταχύτητα ανάκλησης";
    Options["retract_speed"].tooltip = "Η ταχύτητα για ανακλήσεις (ισχύει μόνο για τον κινητήρα του εξωθητήρα).";
    Options["retract_speed"].sidetext = "mm/s";
    Options["retract_speed"].cli = "retract-speed=f@";

    Options["seam_position"].type = coEnum;
    Options["seam_position"].label = "Θέση ραφής";
    Options["seam_position"].category = "Στρώσεις και Περίμετροι";
    Options["seam_position"].tooltip = "Στρώσεις και Περίμετροι";
    Options["seam_position"].cli = "seam-position=s";
    Options["seam_position"].enum_keys_map = ConfigOptionEnum<SeamPosition>::get_enum_values();
    Options["seam_position"].enum_values.push_back("random");
    Options["seam_position"].enum_values.push_back("nearest");
    Options["seam_position"].enum_values.push_back("aligned");
    Options["seam_position"].enum_labels.push_back("Τυχαίο");
    Options["seam_position"].enum_labels.push_back("Κοντινότερο");
    Options["seam_position"].enum_labels.push_back("Ευθύγραμμισμένο");

    Options["skirt_distance"].type = coFloat;
    Options["skirt_distance"].label = "Απόσταση από αντικείμενο";
    Options["skirt_distance"].tooltip = "Απόσταση μεταξύ προέκτασης βάσης και αντικειμένων. Θέστε μηδέν για να συνδέσετε την προέκταση βάσης με τα αντικείμενα και για να πάρετε ένα χείλος με καλύτερη προσκόλληση.";
    Options["skirt_distance"].sidetext = "mm";
    Options["skirt_distance"].cli = "skirt-distance=f";
    Options["skirt_distance"].min = 0;

    Options["skirt_height"].type = coInt;
    Options["skirt_height"].label = "Ύψος προέκτασης βάσης";
    Options["skirt_height"].tooltip = "Το ύψος της προέκτασης βάσης εκφράζεται σε στρώσεις. Δώστε υψηλή τιμή για να χρησιμοποιήσετε την προέκταση βάσης ως ασπίδα ενάντια στα πρόχειρα σχέδια.";
    Options["skirt_height"].sidetext = "στρώσεις";
    Options["skirt_height"].cli = "skirt-height=i";

    Options["skirts"].type = coInt;
    Options["skirts"].label = "Επαναλήψεις (ελάχιστες)";
    Options["skirts"].full_label = "Επαναλήψεις προέκτασης βάσης";
    Options["skirts"].tooltip = "Ο αριθμός επαναλήψεων για την προέκταση βάσης. Εάν έχετε θέσει το ελάχιστο μήκος εξώθησης, ο αριθμός των επαναλήψεων ίσως είναι μεγαλύτερος από αυτόν που ρυθμίζεται εδώ. Θέστε μηδέν για απενεργοποίηση της προέκτασης βάσης εντελώς.";
    Options["skirts"].cli = "skirts=i";
    Options["skirts"].min = 0;
    
    Options["slowdown_below_layer_time"].type = coInt;
    Options["slowdown_below_layer_time"].label = "Επιβράδυνση εάν ο χρόνος εκτύπωσης της στρώσης είναι λιγότερος από";
    Options["slowdown_below_layer_time"].tooltip = "Εάν ο χρόνος εκτύπωσης της στρώσης υπολογίζεται πιο λίγος από αυτό τον αριθμό δευτερολέπτων, η ταχύτητα εκτύπωσης θα χαμηλώσει σταδιακά για να παρατείνει τη διάρκεια έως αυτή τη τιμή.";
    Options["slowdown_below_layer_time"].sidetext = "δευτερόλεπτα κατά προσέγγιση";
    Options["slowdown_below_layer_time"].cli = "slowdown-below-layer-time=i";
    Options["slowdown_below_layer_time"].width = 60;
    Options["slowdown_below_layer_time"].min = 0;
    Options["slowdown_below_layer_time"].max = 1000;

    Options["small_perimeter_speed"].type = coFloatOrPercent;
    Options["small_perimeter_speed"].label = "Μικρές περίμετροι";
    Options["small_perimeter_speed"].category = "Ταχύτητα";
    Options["small_perimeter_speed"].tooltip = "Αυτή η ξεχωριστή ρύθμιση θα επηρεάσει την ταχύτητα των περιμέτρων που έχουν ακτίνα <=6.5mm (συνήθως τρύπες). Εάν εκφραστεί σε ποσοστό (για παράδειγμα: 80%) θα υπολογιστεί βάση της ρύθμισης ταχύτητας εκτύπωσης των περιμέτρων παραπάνω. Θέστε μηδέν για αυτόματο υπολογισμό.";
    Options["small_perimeter_speed"].sidetext = "mm/s ή %";
    Options["small_perimeter_speed"].cli = "small-perimeter-speed=s";
    Options["small_perimeter_speed"].ratio_over = "perimeter_speed";
    Options["small_perimeter_speed"].min = 0;

    Options["solid_infill_below_area"].type = coFloat;
    Options["solid_infill_below_area"].label = "Όριο γεμίσματος στερεάς περιοχής";
    Options["solid_infill_below_area"].category = "Εσωτερικό γέμισμα";
    Options["solid_infill_below_area"].tooltip = "Επιβολή συμπαγούς γεμίσματος για περιοχές μικρότερης επιφάνειας από το δωθέν όριο.";
    Options["solid_infill_below_area"].sidetext = "mm²";
    Options["solid_infill_below_area"].cli = "solid-infill-below-area=f";
    Options["solid_infill_below_area"].min = 0;

    Options["solid_infill_extruder"].type = coInt;
    Options["solid_infill_extruder"].label = "Εξωθητήρας στερεού εσωτερικού γεμίσματος";
    Options["solid_infill_extruder"].category = "Εξωθητήρες";
    Options["solid_infill_extruder"].tooltip = "Ο εξωθητήρας που χρησιμοποιείται όταν εκτυπώνεται στερεό εωτερικό γέμισμα.";
    Options["solid_infill_extruder"].cli = "solid-infill-extruder=i";
    Options["solid_infill_extruder"].min = 1;

    Options["solid_infill_every_layers"].type = coInt;
    Options["solid_infill_every_layers"].label = "Στερεό γέμισμα κάθε";
    Options["solid_infill_every_layers"].category = "Εσωτερικό γέμισμα";
    Options["solid_infill_every_layers"].tooltip = "Αυτή η λειτουργία επιτρέπει μια στερεά στρώση για κάθε αριθμό στρώσεων που έχει δωθεί. Μηδέν για απενεργοποίηση. Μπορείτε να θέσετε οποιαδήποτε τιμή (για παράδειγμα 9999); Το Slic3r αυτόματα θα επιλέξει να συνδυάσει τον μέγιστο δυνατό αριθμό στρώσεων ανάλογα με τη διάμετρο των ακροφύσιων και το ύψος της στρώσης.";
    Options["solid_infill_every_layers"].sidetext = "στρώσεις";
    Options["solid_infill_every_layers"].cli = "solid-infill-every-layers=i";
    Options["solid_infill_every_layers"].min = 0;

    Options["solid_infill_extrusion_width"].type = coFloatOrPercent;
    Options["solid_infill_extrusion_width"].label = "Στερεό εσωτερικό γέμισμα";
    Options["solid_infill_extrusion_width"].category = "Πλάτος Εξώθησης";
    Options["solid_infill_extrusion_width"].tooltip = "Δώστε μη μηδενική τιμή για να θέσετε χειροκίνητα το μήκος εξώθησης για εσωτερικό γέμισμα των στερεών επιφανειών. Εάν εκφραστεί σε ποσοστό (για παράδειγμα: 90%) θα υπολογιστεί με βάση το ύψος της στρώσης.";
    Options["solid_infill_extrusion_width"].sidetext = "mm ή % (αφήστε 0 για προεπιλεγμένο)";
    Options["solid_infill_extrusion_width"].cli = "solid-infill-extrusion-width=s";

    Options["solid_infill_speed"].type = coFloatOrPercent;
    Options["solid_infill_speed"].label = "Στερεό εσωτερικό γέμισμα";
    Options["solid_infill_speed"].category = "Ταχύτητα";
    Options["solid_infill_speed"].tooltip = "Ταχύτητα εκτύπωσης στερεών περιοχών (κορυφή/πάτωμα/εσωτερικά οριζόντια κελιά). Μπορεί να εκφραστεί σε ποσοστό (για παράδειγμα: 80%) με βάση την προεπιλεγμένη ταχύτητα γεμίσματος. Θέστε μηδέν για αυτόματο.";
    Options["solid_infill_speed"].sidetext = "mm/s ή %";
    Options["solid_infill_speed"].cli = "solid-infill-speed=s";
    Options["solid_infill_speed"].ratio_over = "infill_speed";
    Options["solid_infill_speed"].aliases.push_back("solid_infill_feed_rate");
    Options["solid_infill_speed"].min = 0;

    Options["solid_layers"].type = coInt;
    Options["solid_layers"].label = "Στερεές στρώσεις";
    Options["solid_layers"].tooltip = "Ο αριθμός των στερεών στρώσεων για να δημιουργηθούν στις άνω και κάτω επιφάνειες.";
    Options["solid_layers"].cli = "solid-layers=i";
    Options["solid_layers"].shortcut.push_back("top_solid_layers");
    Options["solid_layers"].shortcut.push_back("bottom_solid_layers");
    Options["solid_layers"].min = 0;

    Options["spiral_vase"].type = coBool;
    Options["spiral_vase"].label = "Δοχείο σπιράλ";
    Options["spiral_vase"].tooltip = "Αυτή η λειτουργία θα ανυψώσει τον Z σταδιακά καθώς εκτυπώνει ένα αντικείμενο μονού-τοίχου με σκοπό να αφαιρέσει κάθε ορατή ραφή. Αυτή η επιλογή απαιτεί μια μονή περίμετρο, χωρίς εσωτερικό γέμισμα, χωρίς άνω στερεές στρώσεις και χωρίς υλικά υποστήριξης. Μπορείτε ακόμα να θέσετε οποιοδήποτε αριθμό επαναλήψεων κάτω στερεών στρώσεων όπως προέκταση βάσης/χείλος. Δεν θα λειτουργήσει όταν εκτυπώνετε περισσότερα από ένα αντικείμενο.";
    Options["spiral_vase"].cli = "spiral-vase!";

    Options["standby_temperature_delta"].type = coInt;
    Options["standby_temperature_delta"].label = "Μεταβολή θερμοκρασίας";
    Options["standby_temperature_delta"].tooltip = "Διαφορά θερμοκρασίας που εφαρμόζεται όταν ένας εξωθητήρας δεν είναι ενεργός.";
    Options["standby_temperature_delta"].sidetext = "∆°C";
    Options["standby_temperature_delta"].cli = "standby-temperature-delta=i";
    Options["standby_temperature_delta"].min = -400;
    Options["standby_temperature_delta"].max = 400;

    Options["start_gcode"].type = coString;
    Options["start_gcode"].label = "G-code έναρξης";
    Options["start_gcode"].tooltip = "Αυτή η διαδικασία εκκίνησης εισάγεται στην αρχή, αφού η πλατφόρμα έχει φτάσει την επιθυμητή θερμοκρασία και ο εξωθητήρας μόλις ξεκίνησε να θερμαίνεται, αλλά πριν ο εξωθητήρας φτάσει στην τελική θερμοκρασία. Εάν το Slic3r ανιχνεύσει M104 ή M190 στους προσαρμοσμένους σας κώδικες, τέτοιες εντολές δεν θα γίνουν προθέμα αυτόματα ώστε να είστε ελεύθεροι να προσαρμόσετε την σειρά των εντολών θέρμανσης και άλλες λειτουργίες. Σημειώστε ότι μπορείτε να χρησιμοποιήσετε μεταβλητές για όλες της ρυθμίσεις του Slic3r, έτσι μπορείτε να βάλετε μία \"M109 S[first_layer_temerature]\" εντολή οπουδήποτε θέλετε.";
    Options["start_gcode"].cli = "start-gcode=s";
    Options["start_gcode"].multiline = true;
    Options["start_gcode"].full_width = true;
    Options["start_gcode"].height = 120;

    Options["support_material"].type = coBool;
    Options["support_material"].label = "Δημιουργία υλικού υποστήριξης";
    Options["support_material"].category = "Υλικό υποστήριξης";
    Options["support_material"].tooltip = "Ενεργοποίηση δημιουργίας υλικού υποστήριξης.";
    Options["support_material"].cli = "support-material!";

    Options["support_material_angle"].type = coInt;
    Options["support_material_angle"].label = "Γωνία μοτίβου";
    Options["support_material_angle"].category = "Υλικό υποστήριξης";
    Options["support_material_angle"].tooltip = "Χρησιμοποιήστε αυτή τη ρύθμιση για να περιστρέψετε το μοτίβο υλικού υποστήριξης στο οριζόντιο επίπεδο.";
    Options["support_material_angle"].sidetext = "°";
    Options["support_material_angle"].cli = "support-material-angle=i";
    Options["support_material_angle"].min = 0;
    Options["support_material_angle"].max = 359;

    Options["support_material_contact_distance"].type = coFloat;
    Options["support_material_contact_distance"].gui_type = "f_enum_open";
    Options["support_material_contact_distance"].label = "Απόσταση επαφής του Z";
    Options["support_material_contact_distance"].category = "Υλικό υποστήριξης";
    Options["support_material_contact_distance"].tooltip = "Η κάθετη απόσταση μεταξύ αντικειμένου και επιφάνειας υλικού υποστήριξης. Θέτοντας το σε μηδέν αποτρέπεται επίσης το Slic3r να χρησιμοποιήσει ταχύτητα και ροή γέφυρας για την πρώτη στρώση αντικειμένου.";
    Options["support_material_contact_distance"].sidetext = "mm";
    Options["support_material_contact_distance"].cli = "support-material-contact-distance=f";
    Options["support_material_contact_distance"].min = 0;
    Options["support_material_contact_distance"].enum_values.push_back("0");
    Options["support_material_contact_distance"].enum_values.push_back("0.2");
    Options["support_material_contact_distance"].enum_labels.push_back("0 (εύλυτο)");
    Options["support_material_contact_distance"].enum_labels.push_back("0.2 (αποσπώμενο)");

    Options["support_material_enforce_layers"].type = coInt;
    Options["support_material_enforce_layers"].label = "Επιβολή στήριξης για τις πρώτες";
    Options["support_material_enforce_layers"].category = "Υλικό υποστήριξης";
    Options["support_material_enforce_layers"].tooltip = "Δημιουργία υλικού υποστήριξης για τον προκαθορισμένο αριθμό στρώσεων μετρώντας από κάτω, άσχετα από οτιδήποτε κανονικό υλικό υποστήριξης είναι ενεργοποιημένο ή όχι και άσχετα από οποιοδήποτε όριο γωνίας. Αυτή είναι μια χρήσιμη ρύθμιση για να έχουμε περισσότερη προσκόλληση σε αντικείμενα που έχουν πολύ λεπτό ή μικρό πάτημα στην πλατφόρμα.";
    Options["support_material_enforce_layers"].sidetext = "στρώσεις";
    Options["support_material_enforce_layers"].cli = "support-material-enforce-layers=f";
    Options["support_material_enforce_layers"].full_label = "Επιβολή στήριξης για τις πρώτες Ν στρώσεις";
    Options["support_material_enforce_layers"].min = 0;

    Options["support_material_extruder"].type = coInt;
    Options["support_material_extruder"].label = "Εξωθητήρας υλικού στήριξης/σχεδίας/προέκταση βάσης";
    Options["support_material_extruder"].category = "Εξωθητήρες";
    Options["support_material_extruder"].tooltip = "Ο εξωθητήρας που θα χρησιμοποιηθεί όταν εκτυπώνεται υλικό στήριξης, σχεδίας ή προέκταση βάσης.";
    Options["support_material_extruder"].cli = "support-material-extruder=i";
    Options["support_material_extruder"].min = 1;

    Options["support_material_extrusion_width"].type = coFloatOrPercent;
    Options["support_material_extrusion_width"].label = "Υλικό στήριξης";
    Options["support_material_extrusion_width"].category = "Πλάτος εξώθησης";
    Options["support_material_extrusion_width"].tooltip = "Δώστε μη μηδενική τιμή για να ορίσετε χειροκίνητα το πλάτος εξώθησης για το υλικό στήριξης. Εάν εκφραστεί σε ποσοστό (για παράδειγμα: 90%) θα υπολογιστεί με βάση το ύψος της στρώσης.";
    Options["support_material_extrusion_width"].sidetext = "mm ή % (αφήστε 0 για προεπιλεγμένο)";
    Options["support_material_extrusion_width"].cli = "support-material-extrusion-width=s";

    Options["support_material_interface_extruder"].type = coInt;
    Options["support_material_interface_extruder"].label = "εξωθητήρας για το υλικό υποστήριξης και για το σχεδίας";
    Options["support_material_interface_extruder"].category = "Εξωθητήρες";
    Options["support_material_interface_extruder"].tooltip = "Ο εξωθητήρας που χρησιμοποιείται όταν εκτυπώνεται η διεπαφή του υλικού υποστήριξης. Αυτό επηρεάζει και το σχεδίας.";
    Options["support_material_interface_extruder"].cli = "support-material-interface-extruder=i";
    Options["support_material_interface_extruder"].min = 1;

    Options["support_material_interface_layers"].type = coInt;
    Options["support_material_interface_layers"].label = "Στρώσεις διεπαφών";
    Options["support_material_interface_layers"].category = "Υλικό υποστήριξης";
    Options["support_material_interface_layers"].tooltip = "Ο αριθμός των στρώσεων των διεπαφών που εισάγονται ανάμεσα στα αντικείμενα και το υλικό υποστήριξης.";
    Options["support_material_interface_layers"].sidetext = "στρώσεις";
    Options["support_material_interface_layers"].cli = "support-material-interface-layers=i";
    Options["support_material_interface_layers"].min = 0;

    Options["support_material_interface_spacing"].type = coFloat;
    Options["support_material_interface_spacing"].label = "Μοτίβο διαστήματος διεπαφών";
    Options["support_material_interface_spacing"].category = "Υλικό υποστήριξης";
    Options["support_material_interface_spacing"].tooltip = "Διάστημα μεταξύ των γραμμών των διεπαφών. Θέστε μηδέν για να πάρετε μια συμπαγή διεπαφή.";
    Options["support_material_interface_spacing"].sidetext = "mm";
    Options["support_material_interface_spacing"].cli = "support-material-interface-spacing=f";
    Options["support_material_interface_spacing"].min = 0;

    Options["support_material_interface_speed"].type = coFloatOrPercent;
    Options["support_material_interface_speed"].label = "Διεπαφή υλικού υποστήριξης";
    Options["support_material_interface_speed"].category = "Υλικό υποστήριξης";
    Options["support_material_interface_speed"].tooltip = "Ταχύτητα εκτύπωσης στρώσεων διεπαφής υλικού υποστήριξης. Εάν εκφράζεται σε ποσοστό (για παράδειγμα: 50%) θα υπολογιστεί με βάση την ταχύτητα υλικού υποστήριξης.";
    Options["support_material_interface_speed"].sidetext = "mm ή %";
    Options["support_material_interface_speed"].cli = "support-material-interface-speed=s";
    Options["support_material_interface_speed"].ratio_over = "support_material_speed";
    Options["support_material_interface_speed"].min = 0;

    Options["support_material_pattern"].type = coEnum;
    Options["support_material_pattern"].label = "Μοτίβο";
    Options["support_material_pattern"].category = "Υλικό υποστήριξης";
    Options["support_material_pattern"].tooltip = "Το μοτίβο που χρησιμοποιείται για να δημιουργηθεί το υλικό υποστήριξης.";
    Options["support_material_pattern"].cli = "support-material-pattern=s";
    Options["support_material_pattern"].enum_keys_map = ConfigOptionEnum<SupportMaterialPattern>::get_enum_values();
    Options["support_material_pattern"].enum_values.push_back("rectilinear");
    Options["support_material_pattern"].enum_values.push_back("rectilinear-grid");
    Options["support_material_pattern"].enum_values.push_back("honeycomb");
    Options["support_material_pattern"].enum_values.push_back("pillars");
    Options["support_material_pattern"].enum_labels.push_back("rectilinear");
    Options["support_material_pattern"].enum_labels.push_back("rectilinear grid");
    Options["support_material_pattern"].enum_labels.push_back("honeycomb");
    Options["support_material_pattern"].enum_labels.push_back("pillars");

    Options["support_material_spacing"].type = coFloat;
    Options["support_material_spacing"].label = "Μοτίβο διαστημάτων";
    Options["support_material_spacing"].category = "Υλικό υποστήριξης";
    Options["support_material_spacing"].tooltip = "Διάστημα μεταξύ γραμμών υλικού υποστήριξης.";
    Options["support_material_spacing"].sidetext = "mm";
    Options["support_material_spacing"].cli = "support-material-spacing=f";
    Options["support_material_spacing"].min = 0;

    Options["support_material_speed"].type = coFloat;
    Options["support_material_speed"].label = "Υλικό υποστήριξης";
    Options["support_material_speed"].category = "Υλικό υποστήριξης";
    Options["support_material_speed"].tooltip = "Ταχύτητα εκτύπωσης υλικού υποστήριξης";
    Options["support_material_speed"].sidetext = "mm/s";
    Options["support_material_speed"].cli = "support-material-speed=f";
    Options["support_material_speed"].min = 0;

    Options["support_material_threshold"].type = coInt;
    Options["support_material_threshold"].label = "Όριο προεξοχής";
    Options["support_material_threshold"].category = "Υλικό υποστήριξης";
    Options["support_material_threshold"].tooltip = "Δεν θα δημιουργηθεί υλικό υποστήριξης για προεξοχές των οποίων η κλίση της γωνίας (90° = κάθετα) είναι πάνω από το δοθέν όριο. Με άλλα λόγια, αυτή η τιμή αντιπροσωπεύει την πιο οριζόντια κλίση (μετρώντας την από τον οριζόντιο άξονα) που μπορείτε να εκτυπώσετε χωρίς υλικό υποστήριξης. Θέστε μηδέν για αυτόματο εντοπισμό (προτείνεται).";
    Options["support_material_threshold"].sidetext = "°";
    Options["support_material_threshold"].cli = "support-material-threshold=i";
    Options["support_material_threshold"].min = 0;
    Options["support_material_threshold"].max = 90;

    Options["temperature"].type = coInts;
    Options["temperature"].label = "Άλλες στρώσεις";
    Options["temperature"].tooltip = "Η θερμοκρασία του εξωθητήρα για της στρώσεις μετά την πρώτη. Θέστε μηδέν για απενεργοποίηση των εντολών ελέγχου θερμοκρασίας στην έξοδο.";
    Options["temperature"].cli = "temperature=i@";
    Options["temperature"].full_label = "Θερμοκρασία";
    Options["temperature"].max = 0;
    Options["temperature"].max = 400;

    Options["thin_walls"].type = coBool;
    Options["thin_walls"].label = "Εντοπισμός λεπτών τοιχωμάτων";
    Options["thin_walls"].category = "Στρώσεις και Περίμετροι";
    Options["thin_walls"].tooltip = "Εντοπισμός τοίχων μονού-πλάτους (τμήματα όπου 2 εξωθήσεις δεν χωράνε και χρειάζεται να τις βάλουμε σε μια μονή γραμμή  )";
    Options["thin_walls"].cli = "thin-walls!";

    Options["threads"].type = coInt;
    Options["threads"].label = "Νήματα εντολών";
    Options["threads"].tooltip = "Χρησιμοποιούνται νήματα εντολών προς τον επεξεργαστή για την παραλληλοποίηση εργασιών που παίρνουν πολύ χρόνο. Ο βέλτιστος αριθμός νημάτων είναι ελαφρώς πάνω από τον αριθμό των διαθέσιμων πυρήνων/επεξεργαστών.";
    Options["threads"].cli = "threads|j=i";
    Options["threads"].readonly = true;
    Options["threads"].min = 1;
    Options["threads"].max = 16;

    Options["toolchange_gcode"].type = coString;
    Options["toolchange_gcode"].label = "G-code αλλαγής εργαλείου";
    Options["toolchange_gcode"].tooltip = "Αυτός ο custom κώδικας εισάγεται ακριβώς πριν από κάθε αλλαγή του εξωθητήρα. Σημειώστε ότι μπορείτε να χρησιμοποιήσετε μεταβλητές placeholder για όλες τις ρυθμίσεις του Slic3r καθώς επίσης τα [previous_extruder] και [next_extruder].";
    Options["toolchange_gcode"].cli = "toolchange-gcode=s";
    Options["toolchange_gcode"].multiline = true;
    Options["toolchange_gcode"].full_width = true;
    Options["toolchange_gcode"].height = 50;

    Options["top_infill_extrusion_width"].type = coFloatOrPercent;
    Options["top_infill_extrusion_width"].label = "Άνω συμπαγές εσωτερικό γέμισμα";
    Options["top_infill_extrusion_width"].category = "Πλάτος εξώθησης";
    Options["top_infill_extrusion_width"].tooltip = "Δώστε μη μηδενική τιμή για να θέσετε χειροκίνητα το πλάτος εξώθησης για εσωτερικό γέμισμα των άνω επιφανειών. Μπορεί να θέλετε να χρησιμοποιήσετε λεπτότερα υλικά για να να συμπληρώσετε όλες τις στενές περιοχές και να πάρετε ένα πιο λείο τελείωμα. Εάν εκφραστεί σε ποσοστό (για παράδειγμα: 90%) θα υπολογιστεί με βάση το ύψος της στρώσης.";
    Options["top_infill_extrusion_width"].sidetext = "mm ή % (αφήστε 0 για προεπιλεγμένο)";
    Options["top_infill_extrusion_width"].cli = "top-infill-extrusion-width=s";

    Options["top_solid_infill_speed"].type = coFloatOrPercent;
    Options["top_solid_infill_speed"].label = "Άνω συμπαγές γέμισμα";
    Options["top_solid_infill_speed"].category = "Ταχύτητα";
    Options["top_solid_infill_speed"].tooltip = "Ταχύτητα εκτύπωσης των άνω συμπαγών στρώσεων (αυτό εφαρμόζεται μόνο στα ανώτατα εξωτερικά στρώματα και όχι στις εσωτερικές τους συμπαγείς στρώσεις). Μπορεί να θέλετε να το επιβραδύνετε για να πάρετε ένα καλύτερο τελείωμα επιφάνειας. Αυτό μπορει να εκφραστεί σε ποσοστό (για παράδειγμα: 80%) βάσει της ταχύτητας συμπαγούς γεμίσματος. Θέστε μηδέν για αυτόματο.";
    Options["top_solid_infill_speed"].sidetext = "mm ή %";
    Options["top_solid_infill_speed"].cli = "top-solid-infill-speed=s";
    Options["top_solid_infill_speed"].ratio_over = "solid_infill_speed";
    Options["top_solid_infill_speed"].min = 0;

    Options["top_solid_layers"].type = coInt;
    Options["top_solid_layers"].label = "Κορυφή";
    Options["top_solid_layers"].category = "Στρώσεις και Περίμετροι";
    Options["top_solid_layers"].tooltip = "Ο αριθμός των συμπαγών στρώσεων που δημιουργούνται στις άνω επιφάνειες.";
    Options["top_solid_layers"].cli = "top-solid-layers=i";
    Options["top_solid_layers"].full_label = "Άνω συμπαγές γέμισμα";
    Options["top_solid_layers"].min = 0;

    Options["travel_speed"].type = coFloat;
    Options["travel_speed"].label = "Μετακίνηση";
    Options["travel_speed"].tooltip = "Ταχύτητα μετακίνησης (άλματα μεταξύ απόστασης σημείων εξώθησης).";
    Options["travel_speed"].sidetext = "mm/s";
    Options["travel_speed"].cli = "travel-speed=f";
    Options["travel_speed"].aliases.push_back("travel_feed_rate");
    Options["travel_speed"].min = 1;

    Options["use_firmware_retraction"].type = coBool;
    Options["use_firmware_retraction"].label = "Χρήση ανάκλησης firmware";
    Options["use_firmware_retraction"].tooltip = "Αυτή η πειραματική ρύθμιση χρησιμοποιεί εντολές G10 και G11 για να μπορεί το λογισμικό να έχει τον έλεγχο της ανάκλησης. Αυτό υποστηρίζεται μόνο σε πρόσφατα Marlin.";
    Options["use_firmware_retraction"].cli = "use-firmware-retraction!";

    Options["use_relative_e_distances"].type = coBool;
    Options["use_relative_e_distances"].label = "Χρησιμοποιήστε σχετικές αποστάσεις E";
    Options["use_relative_e_distances"].tooltip = "Εάν το firmware σας απαιτεί σχετικές τιμές E, επιλέξτε αυτό, αλλιώς αφήστε το μη επιλεγμένο. Τα περισσότερα firmware χρησιμοποιούν απόλυτες τιμές";
    Options["use_relative_e_distances"].cli = "use-relative-e-distances!";

    Options["use_volumetric_e"].type = coBool;
    Options["use_volumetric_e"].label = "Χρησιμοποιήστε ογκομετρικό E";
    Options["use_volumetric_e"].tooltip = "Αυτή η πειραματική ρύθμιση χρησιμοποιεί τις εξόδους των τιμών E σε κυβικά χιλιοστά αντί για γραμμικά χιλιοστά. Εάν το firmware σας δεν γνωρίζει ήδη την διάμετρο του νήματος, μπορείτε να βάλετε στην αρχή του G-code εντολές όπως 'M200 D[filament_diameter_0] T0' με σκοπό να ενεργοποιήσετε την ογκομετρική λειτουργία και να χρησιμοποιήσετε τη διάμετρο του νήματος που σχετίζεται με το επιλεγμένο νήμα στο Slic3r. Αυτό υποστηρίζεται μόνο σε πρόσφατα Marlin.";
    Options["use_volumetric_e"].cli = "use-volumetric-e!";

    Options["vibration_limit"].type = coFloat;
    Options["vibration_limit"].label = "Όριο κραδασμών (καταργήθηκε)";
    Options["vibration_limit"].tooltip = "Αυτή η πειραματική επιλογή θα επιβραδύνει εκείνες τις κινήσεις που χτυπάνε το ρυθμισμένο όριο συχνότητας. Ο σκοπός της οριοθέτησης των κραδασμών είναι η αποφυγή μηχανικού συντονισμού. Θέστε μηδέν για απενεργοποίηση.";
    Options["vibration_limit"].sidetext = "Hz";
    Options["vibration_limit"].cli = "vibration-limit=f";
    Options["vibration_limit"].min = 0;

    Options["wipe"].type = coBools;
    Options["wipe"].label = "Σκούπισμα ενώ γίνεται ανάκληση";
    Options["wipe"].tooltip = "Αυτή το πεδίο θα μετακινήσει το ακροφύσιο ενώ γίνεται ανάσυρση για να ελαχιστοποιήσει τις ενδεχόμενες σταγόνες από εξωθητήρες με διαρροές.";
    Options["wipe"].cli = "wipe!";

    Options["xy_size_compensation"].type = coFloat;
    Options["xy_size_compensation"].label = "Αντιστάθμιση Μεγέθους XY";
    Options["xy_size_compensation"].category = "Για προχωρημένους";
    Options["xy_size_compensation"].tooltip = "Το αντικείμενο θα μεγαλώσει/μικρύνει στους άξονες XY κατά την διαμορφωμένη τιμή (αρνητική = προς τα μέσα, θετική = προς τα έξω). Αυτό ίσως είναι χρήσιμο για να ρυθμιστούν με ακρίβεια μεγέθη τρυπών.";
    Options["xy_size_compensation"].sidetext = "mm";
    Options["xy_size_compensation"].cli = "xy-size-compensation=f";

    Options["z_offset"].type = coFloat;
    Options["z_offset"].label = "Αντιστάθμιση Ζ";
    Options["z_offset"].tooltip = "Αυτή η τιμή θα προστεθεί (ή αφαιρεθεί) από όλες τις Ζ συντεταγμένες στο εξαγόμενο G-code. Αυτό χρησιμοποιείται για να αντισταθμίσει κακό σταμάτημα στον Ζ άξονα. Για παράδειγμα αν ο διακόπτης σταματήματος του Ζ άξονα στη θέση 0 στη πραγματικότητα αφήνει τo ακροφύσιο 0.3mm από τη πλατφόρμα, δώστε τιμή -0.3 (ή ρυθμίστε τον διακόπτη)";
    Options["z_offset"].sidetext = "mm";
    Options["z_offset"].cli = "z-offset=f";
    
    return Options;
};

t_optiondef_map PrintConfigDef::def = PrintConfigDef::build_def();

void
DynamicPrintConfig::normalize() {
    if (this->has("extruder")) {
        int extruder = this->option("extruder")->getInt();
        this->erase("extruder");
        if (extruder != 0) {
            if (!this->has("infill_extruder"))
                this->option("infill_extruder", true)->setInt(extruder);
            if (!this->has("perimeter_extruder"))
                this->option("perimeter_extruder", true)->setInt(extruder);
            if (!this->has("support_material_extruder"))
                this->option("support_material_extruder", true)->setInt(extruder);
            if (!this->has("support_material_interface_extruder"))
                this->option("support_material_interface_extruder", true)->setInt(extruder);
        }
    }
    
    if (!this->has("solid_infill_extruder") && this->has("infill_extruder"))
        this->option("solid_infill_extruder", true)->setInt(this->option("infill_extruder")->getInt());
    
    if (this->has("spiral_vase") && this->opt<ConfigOptionBool>("spiral_vase", true)->value) {
        {
            // this should be actually done only on the spiral layers instead of all
            ConfigOptionBools* opt = this->opt<ConfigOptionBools>("retract_layer_change", true);
            opt->values.assign(opt->values.size(), false);  // set all values to false
        }
        {
            this->opt<ConfigOptionInt>("perimeters", true)->value       = 1;
            this->opt<ConfigOptionInt>("top_solid_layers", true)->value = 0;
            this->opt<ConfigOptionPercent>("fill_density", true)->value  = 0;
        }
    }
}

#ifdef SLIC3RXS
REGISTER_CLASS(DynamicPrintConfig, "Config");
REGISTER_CLASS(PrintObjectConfig, "Config::PrintObject");
REGISTER_CLASS(PrintRegionConfig, "Config::PrintRegion");
REGISTER_CLASS(GCodeConfig, "Config::GCode");
REGISTER_CLASS(PrintConfig, "Config::Print");
REGISTER_CLASS(FullPrintConfig, "Config::Full");
#endif

}
