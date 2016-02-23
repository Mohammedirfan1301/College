#!/usr/bin/perl
use 5.10.0;
use warnings FATAL => 'all';

use File::Temp;
use File::Copy;
use IO::Handle;

sub scm_eval {
    my ($cmdline) = @_;
    my $tmpcmd = File::Temp->new;
    $tmpcmd->say($cmdline);
    my $tmpcode = File::Temp->new;
    copy("ps3c.rkt", $tmpcode) or die "Copy failed: $!";
    open(my $fh, '>>', $tmpcode);
    $fh->say('
(define-namespace-anchor bottlenose-nsa)
(define bottlenose-ns (namespace-anchor->namespace bottlenose-nsa))
(eval (call-with-input-string (vector-ref (current-command-line-arguments) 0) read) bottlenose-ns)');
    my $result = `racket $tmpcode '(load "$tmpcmd")'`;
    chomp $result;
#    print "answer was ", $result, " ";
    return $result;
}

sub scm_equal {
    my ($e0, $e1) = @_;
    my $tmp = File::Temp->new;
    $tmp->say("(equal? $e0 $e1)");
    my $result = `racket -e '(load "$tmp")'`;
    chomp $result;
    return $result eq "#t";
}

use Test::Simple tests => 16;

ok(scm_equal(scm_eval('(title (make-record "Revolver" "The Beatles" 14.99 \'rock 3))'), '"Revolver"'), "title");
ok(scm_equal(scm_eval('(artist (make-record "Revolver" "The Beatles" 14.99 \'rock 3))'), '"The Beatles"'), "artist");
ok(scm_equal(scm_eval('(price (make-record "Revolver" "The Beatles" 14.99 \'rock 3))'), '14.99'), "price");
ok(scm_equal(scm_eval('(category (make-record "Revolver" "The Beatles" 14.99 \'rock 3))'), "\'rock"), "category");
ok(scm_equal(scm_eval('(units-in-stock (make-record "Revolver" "The Beatles" 14.99 \'rock 3))'), "3"), "units-in-stock");
ok(scm_equal(scm_eval('(set! cdDB \'()) (load "freds-db.rkt") (all-titles cdDB)'), '\'("Love, Shelby"
  "Phantom Blues"
  "Dirt"
  "What Does It Take (To Win Your Love)"
  "Midnight Run"
  "Saxphone Colossus"
  "Live at Montreux"
  "Abbey Road"
  "Revolver"
  "The White Album")'), "(all-titles cdDB)");
ok(scm_equal(scm_eval('(set! cdDB \'())(load "freds-db.rkt")(titles-in-stock cdDB)'), '\'("Love, Shelby"
  "Phantom Blues"
  "Dirt"
  "What Does It Take (To Win Your Love)"
  "Midnight Run"
  "Saxphone Colossus"
  "Live at Montreux"
  "Revolver"
  "The White Album")'), "(titles-in-stock cdDB)");
ok(scm_equal(scm_eval('(set! cdDB \'())(load "freds-db.rkt")(restock "Abbey Road" 5 cdDB)'), '\'(("Love, Shelby" "Shelby Lynne" 14.98 country 5)
  ("Phantom Blues" "Taj Mahal" 9.0 blues 3)
  ("Dirt" "Alice in Chains" 12.98 rock 7)
  ("What Does It Take (To Win Your Love)"
   "Jr. Walker & The All Stars"
   9.98
   motown
   3)
  ("Midnight Run" "Bobby Blue Bland" 9.0 blues 2)
  ("Saxphone Colossus" "Sonny Rollins" 12.98 jazz 3)
  ("Live at Montreux" "Miles & Quincy" 17.98 jazz 2)
  ("Abbey Road" "The Beatles" 14.98 rock 5)
  ("Revolver" "The Beatles" 14.98 rock 3)
  ("The White Album" "The Beatles" 19.99 rock 7))'), '(restock "Abbey Road" 5 cdDB)');
ok(scm_equal(scm_eval('(set! cdDB \'())(load "freds-db.rkt")(titles-by "The Beatles" cdDB)'), '\'("Abbey Road" "Revolver" "The White Album")'), '(titles-by "The Beatles" cdDB)');
ok(scm_equal(scm_eval('(set! cdDB \'())(load "freds-db.rkt")(copies-in-stock "Midnight Run" "Bobby Blue Bland" cdDB)'), '2'), '(copies-in-stock "Midnight Run" "Bobby Blue Bland" cdDB)');
ok(scm_equal(scm_eval('(set! cdDB \'())(load "freds-db.rkt")(copies-in-stock "Abbey Road" "The Beatles" cdDB)'), '0'), '(copies-in-stock "Abbey Road" "The Beatles" cdDB)');
# copies-in-stock should return 0 in the case where the record isn't in the db!
ok(scm_equal(scm_eval('(set! cdDB \'())(load "freds-db.rkt")(copies-in-stock "Help!" "The Beatles" cdDB)'), '0'), '(copies-in-stock "Help!" "The Beatles" cdDB)');
ok(scm_equal(scm_eval('(set! cdDB \'())(load "freds-db.rkt")(blues-sale cdDB)'), '\'(("Love, Shelby" "Shelby Lynne" 14.98 country 5)
  ("Phantom Blues" "Taj Mahal" 8.1 blues 3)
  ("Dirt" "Alice in Chains" 12.98 rock 7)
  ("What Does It Take (To Win Your Love)"
   "Jr. Walker & The All Stars"
   9.98
   motown
   3)
  ("Midnight Run" "Bobby Blue Bland" 8.1 blues 2)
  ("Saxphone Colossus" "Sonny Rollins" 12.98 jazz 3)
  ("Live at Montreux" "Miles & Quincy" 17.98 jazz 2)
  ("Abbey Road" "The Beatles" 14.98 rock 0)
  ("Revolver" "The Beatles" 14.98 rock 3)
  ("The White Album" "The Beatles" 19.99 rock 7))'), '(blues-sale cdDB)');
ok(scm_equal(scm_eval('(set! cdDB \'())(load "freds-db.rkt")(carry-cd? "Dirt" "Alice in Chains" cdDB)'), '#t'), '(carry-cd? "Dirt" "Alice in Chains" cdDB)');
ok(scm_equal(scm_eval('(set! cdDB \'())(load "freds-db.rkt")(carry-cd? "Facelift" "Alice in Chains" cdDB)'), '#f'), '(carry-cd? "Facelift" "Alice in Chains" cdDB)');
# this record doesn't exist
ok(scm_equal(scm_eval('(set! cdDB \'())(load "freds-db.rkt")(carry-cd? "Help!" "The Beatles" cdDB)'), '#f'), '(carry-cd? "Help!" "The Beatles" cdDB)');
