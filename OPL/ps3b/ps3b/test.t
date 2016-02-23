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
    copy("ps3b.rkt", $tmpcode) or die "Copy failed: $!";
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
sub scm_equal_sign {
    my ($e0, $e1) = @_;
    my $tmp = File::Temp->new;
    $tmp->say("(equal?/recur (list->vector $e0) (list->vector $e1) =)");
    my $result = `racket -e '(load "$tmp")'`;
    chomp $result;
    return $result eq "#t";
}

use Test::Simple tests => 33;


ok(scm_equal(scm_eval("(double-list1 '(1 2 3))"), "'(2 4 6)"), "(double-list1 '(1 2 3))");
ok(scm_equal(scm_eval("(double-list2 '(1 2 3))"), "'(2 4 6)"), "(double-list2 '(1 2 3))");
ok(scm_equal(scm_eval("(double-list3 '(1 2 3))"), "'(2 4 6)"), "(double-list3 '(1 2 3))");
ok(scm_equal(scm_eval("(square-list1 '(1 2 3))"), "'(1 4 9)"), "(square-list1 '(1 2 3))");
ok(scm_equal(scm_eval("(square-list2 '(1 2 3))"), "'(1 4 9)"), "(square-list2 '(1 2 3))");

# ok(scm_equal(scm_eval("()"), "'()"), "()");
# enum-range-i
ok(scm_equal(scm_eval("(enum-range-i 1 10)"), "'(1 2 3 4 5 6 7 8 9 10)"), "enum-range-i");

# odds
ok(scm_equal(scm_eval("(odds '(1 2 3 4 5 6 7 8 9 10))"), "'(1 3 5 7 9)"), "odds");

# triples
ok(scm_equal(scm_eval("(triples '(1 2 3 4 5 6 7 8 9 10))"), "'(3 6 9 12 15 18 21 24 27 30)"), "triples");

# square-sum

ok(scm_equal(scm_eval("(square-sum my-nats)"), "338350"), "square-sum");

# products
ok(scm_equal(scm_eval("(products my-nats)"), "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000"), "products");

# sum-of-prod-lists
ok(scm_equal(scm_eval("(sum-of-prod-lists '((1 2) (3 4) (5 6)))"), "44"), "(sum-of-prod-lists '((1 2) (3 4) (5 6)))");
ok(scm_equal(scm_eval("(sum-of-prod-lists my-nat-pairs)"), "169150"), "(sum-of-prod-lists my-nat-pairs)");

# sum-of-prods
ok(scm_equal(scm_eval("(sum-of-prods '())"), "0"), "(sum-of-prods '())");
ok(scm_equal(scm_eval("(sum-of-prods '(1 2 3 4 5 6))"), "44"), "(sum-of-prods '(1 2 3 4 5 6))");
ok(scm_equal(scm_eval("(sum-of-prods '(21 39 71 46 98 11 37 36))"), "6495"), "(sum-of-prods '(21 39 71 46 98 11 37 36))");
ok(scm_equal(scm_eval("(sum-of-prods my-nats)"), "169150"), "(sum-of-prods my-nats)");

ok(scm_equal(scm_eval("(map-from-fold square '())"), "'()"), "(map-from-fold square '())");
ok(scm_equal(scm_eval("(map-from-fold square '(1 2 3))"), "'(1 4 9)"), "(map-from-fold square '(1 2 3))");
ok(scm_equal(scm_eval("(map-from-fold square '(1 2 3 4 5 6 7 8 9 10))"), "'(1 4 9 16 25 36 49 64 81 100)"), "(map-from-fold square '(1 2 3 4 5 6 7 8 9 10))");

ok(scm_equal(scm_eval("(append-from-fold '() '(3 4))"), "'(3 4)"), "(append-from-fold '() '(3 4))");
ok(scm_equal(scm_eval("(append-from-fold '(1 2) '(3 4))"), "'(1 2 3 4)"), "(append-from-fold '(1 2) '(3 4))");
ok(scm_equal(scm_eval("(append-from-fold '(1 2) '())"), "'(1 2)"), "(append-from-fold '(1 2) '())");

ok(scm_equal(scm_eval("(length-from-fold '())"), 0), "(length-from-fold '())");
ok(scm_equal(scm_eval("(length-from-fold '(1 2 3 4))"), 4), "(length-from-fold '(1 2 3 4))");
ok(scm_equal(scm_eval("(length-from-fold my-nats)"), 100), "(length-from-fold my-nats)");

ok(scm_equal(scm_eval("(count-leaves '())"), 0), "(count-leaves '())");
ok(scm_equal(scm_eval("(count-leaves '(1 2 3))"), 3), "(count-leaves '(1 2 3))");
ok(scm_equal(scm_eval("(count-leaves '(1 (2 3) 4 (5 6)))"), 6), "(count-leaves '(1 (2 3) 4 (5 6)))");

ok(scm_equal(scm_eval("(my-reverse (list 1 2 3))"), "(reverse (list 1 2 3))"), "(my-reverse (list 1 2 3))");
ok(scm_equal(scm_eval("(my-reverse (list (list 1 2) (list 3 (list 4 5))))"), "(reverse (list (list 1 2) (list 3 (list 4 5))))"), "(my-reverse (list (list 1 2) (list 3 (list 4 5))))");

ok(scm_equal(scm_eval("(deep-reverse (list 1 2 3))"), "'(3 2 1)"), "(deep-reverse (list 1 2 3))");
ok(scm_equal(scm_eval("(deep-reverse (list (list 1 2) (list 3 4)))"), "'((4 3) (2 1))"), "(deep-reverse (list (list 1 2) (list 3 4))");
ok(scm_equal(scm_eval("(deep-reverse (list (list 1 2) (list 3 (list 4 5))))"), "'(((5 4) 3) (2 1))"), "(deep-reverse (list (list 1 2) (list 3 (list 4 5))))");

