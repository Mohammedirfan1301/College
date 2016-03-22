#!/usr/bin/perl
use 5.10.0;
use warnings FATAL => 'all';

use File::Temp;
use File::Copy;
use IO::Handle;

sub scm_eval {
    my ($fname, $cmdline) = @_;
    my $tmpcmd = File::Temp->new;
    $tmpcmd->say($cmdline);
    my $tmpcode = File::Temp->new;
    copy($fname, $tmpcode) or die "Copy failed: $!";
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

use Test::Simple tests => 27;

ok(scm_equal(scm_eval("p1_p2.rkt", "p1_1"), "#t"), "(p1/Exercise 2.76) Answer 1.1");
ok(scm_equal(scm_eval("p1_p2.rkt", "p1_2"), "#t"), "(p1/Exercise 2.76) Answer 1.2");
ok(scm_equal(scm_eval("p1_p2.rkt", "p1_3"), "#t"), "(p1/Exercise 2.76) Answer 1.3");

ok(scm_equal(scm_eval("p1_p2.rkt", "p2_1"), "#t"), "(p2/Exercise 2.77) Answer 2.1");
ok(scm_equal(scm_eval("p1_p2.rkt", "p2_2"), "#t"), "(p2/Exercise 2.77) Answer 2.2");

ok(scm_equal(scm_eval("p3.rkt", "(type-tag (make-rat 3 4))"), "'rational"), "(p3/Basic Setup) Ensure type-tag still work on rationals");
ok(scm_equal(scm_eval("p3.rkt", "(type-tag (make-complex-from-real-imag 1 1))"), "'complex"), "(p3/Basic Setup) Ensure type-tag still work on complex");
ok(scm_equal(scm_eval("p3.rkt", "(mul (make-complex-from-real-imag 1 1) (make-complex-from-mag-ang 2 0))"), "'(complex polar 2.8284271247461903 . 0.7853981633974483)"), "(p3/Basic Setup) Ensure complex arithmetic still works");

ok(scm_equal(scm_eval("p3.rkt", "(number? (attach-tag 'scheme-number 4))"), "#t"), "(p3/Exercise 2.78) Attach-tag of 'scheme-number should be a scheme primitive number type");
ok(scm_equal(scm_eval("p3.rkt", "(type-tag (attach-tag 'scheme-number 4))"), "'scheme-number"), "(p3/Exercise 2.78) Type-tag of 'scheme-number should give 'scheme-number");
ok(scm_equal(scm_eval("p3.rkt", "(type-tag 4)"), "'scheme-number"), "(p3/Exercise 2.78) Type-tag of primitive  number should give 'scheme-number");
ok(scm_equal(scm_eval("p3.rkt", "(contents 4)"), "4"), "(p3/Exercise 2.78) Contents of a primitive number should be that number");
ok(scm_equal(scm_eval("p3.rkt", "(add 95 101)"), "196"), "(p3/Exercise 2.78) add procedure should add primitive numbers correctly");
ok(scm_equal(scm_eval("p3.rkt", "(mul 95 101)"), "9595"), "(p3/Exercise 2.78) mul procedure should multiply primitive numbers correctly");

ok(scm_equal(scm_eval("p4.rkt", "(equ? (make-scheme-number 11) (make-scheme-number 22))"), "#f"), "(p4/Exercise 2.79) equ? should discriminate different scheme-numbers");
ok(scm_equal(scm_eval("p4.rkt", "(equ? (make-scheme-number 22) (make-scheme-number 22))"), "#t"), "(p4/Exercise 2.79) equ? should identify same scheme-numbers");
ok(scm_equal(scm_eval("p4.rkt", "(equ? (make-rat 3 4) (make-rat 22 44))"), "#f"), "(p4/Exercise 2.79) equ? should discriminate different rationals");
ok(scm_equal(scm_eval("p4.rkt", "(equ? (make-rat 22 44) (make-rat 22 44))"), "#t"), "(p4/Exercise 2.79) equ? should identify same rationals");
ok(scm_equal(scm_eval("p4.rkt", "(equ? (make-complex-from-mag-ang 2 0) (make-complex-from-real-imag 1 1))"), "#f"), "(p4/Exercise 2.79) equ? should discriminate different complex numbers");
ok(scm_equal(scm_eval("p4.rkt", "(equ? (make-complex-from-real-imag 1 1) (make-complex-from-real-imag 1 1))"), "#t"), "(p4/Exercise 2.79) equ? should identify same complex numbers");

ok(-f "p5.rkt", "(p5/Exercise 2.81a) File Exists. This problem is not autograded- for now, take some points!");
ok(-f "p5.rkt", "(p5/Exercise 2.81a) File Exists. This problem is not autograded- for now, take some points!");
ok(-f "p5.rkt", "(p5/Exercise 2.81b) File Exists. This problem is not autograded- for now, take some points!");
ok(-f "p5.rkt", "(p5/Exercise 2.81b) File Exists. This problem is not autograded- for now, take some points!");
ok(-f "p5.rkt", "(p5/Exercise 2.81c) File Exists. This problem is not autograded- for now, take some points!");
ok(-f "p5.rkt", "(p5/Exercise 2.81c) File Exists. This problem is not autograded- for now, take some points!");
ok(-f "p5.rkt", "(p5/Exercise 2.81c) File Exists. This problem is not autograded- for now, take some points!");
