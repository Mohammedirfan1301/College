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

use Test::Simple tests => 52;

ok(scm_equal(scm_eval("exercise2-58.rkt", "(make-sum 'x 3)"), "'(x + 3)"), "infix make-sum constructor");
ok(scm_equal(scm_eval("exercise2-58.rkt", "(sum? (make-sum 'x 3))"), "#t"), "infix sum predicate");
ok(scm_equal(scm_eval("exercise2-58.rkt", "(addend (make-sum 'x 3))"), "'x"), "infix addend selector");
ok(scm_equal(scm_eval("exercise2-58.rkt", "(augend (make-sum 'x 3))"), "3"), "infix augend selector");

ok(scm_equal(scm_eval("exercise2-58.rkt", "(make-product 'x 3)"), "'(x * 3)"), "infix make-product constructor");
ok(scm_equal(scm_eval("exercise2-58.rkt", "(product? (make-product 'x 3))"), "#t"), "infix product predicate");
ok(scm_equal(scm_eval("exercise2-58.rkt", "(multiplier (make-product 'x 3))"), "'x"), "infix multiplier selector");
ok(scm_equal(scm_eval("exercise2-58.rkt", "(multiplicand (make-product 'x 3))"), "3"), "infix multiplicand selector");

ok(scm_equal(scm_eval("exercise2-58.rkt", "(make-exponentiation 'x 3)"), "'(x ** 3)"), "infix make-exponentiation constructor");
ok(scm_equal(scm_eval("exercise2-58.rkt", "(exponentiation? (make-exponentiation 'x 3))"), "#t"), "infix exponentiation predicate");
ok(scm_equal(scm_eval("exercise2-58.rkt", "(base (make-exponentiation 'x 3))"), "'x"), "infix exponentiation base selector");
ok(scm_equal(scm_eval("exercise2-58.rkt", "(exponent (make-exponentiation 'x 3))"), "3"), "infix exponentiation exponent selector");

ok(scm_equal(scm_eval("exercise2-58.rkt", "(deriv '(x + 3) 'x)"), "1"), "(deriv '(x + 3) 'x)");
ok(scm_equal(scm_eval("exercise2-58.rkt", "(deriv '(x * (y * (x + 3))) 'x)"), "'((x * y) + (y * (x + 3)))"), "(deriv '(x * (y * (x + 3))) 'x)");
ok(scm_equal(scm_eval("exercise2-58.rkt", "(deriv '((x * y) * (x + 3)) 'x)"), "'((x * y) + (y * (x + 3)))"), "(deriv '((x * y) * (x + 3)) 'x)");
ok(scm_equal(scm_eval("exercise2-58.rkt", "(deriv '((x ** 3) + (x ** 2)) 'x)"), "'((3 * (x ** 2)) + (2 * x))"), "(deriv '((x ** 3) + (x ** 2)) 'x)");

ok(scm_equal(scm_eval("exercise2-57.rkt", "(make-sum 'x 3)"), "'(+ x 3)"), "(make-sum 'x 3) is '(+ x 3)");
ok(scm_equal(scm_eval("exercise2-57.rkt", "(make-sum 1 2)"), "3"), "(make-sum 1 2) is 3");
ok(scm_equal(scm_eval("exercise2-57.rkt", "(make-sum 'x 0)"), "'x"), "(make-sum 'x 0) is 'x");
ok(scm_equal(scm_eval("exercise2-57.rkt", "(make-sum 0 'x)"), "'x"), "(make-sum 0 'x) is 'x");
ok(scm_equal(scm_eval("exercise2-57.rkt", "(make-sum 'x)"), "'x"), "(make-sum 'x) is 'x");
ok(scm_equal(scm_eval("exercise2-57.rkt", "(make-sum 'x 'y 'z)"), "'(+ x y z)"), "(make-sum 'x 'y 'z) is '(+ x y z)");

ok(scm_equal(scm_eval("exercise2-57.rkt", "(addend '(+ x 3))"), "'x"), "(addend '(+ x 3)) is 'x");
ok(scm_equal(scm_eval("exercise2-57.rkt", "(augend '(+ x 3))"), "3"), "(augend '(+ x 3)) is 3");
ok(scm_equal(scm_eval("exercise2-57.rkt", "(addend '(+ x y z))"), "'x"), "(addend '(+ x y z)) is 'x");
ok(scm_equal(scm_eval("exercise2-57.rkt", "(augend '(+ x y z))"), "'(+ y z)"), "(augend '(+ x y z)) is '(+ y z)");

ok(scm_equal(scm_eval("exercise2-57.rkt", "(make-product 'x 3)"), "'(* x 3)"), "(make-product 'x 3) is '(* x 3)");
ok(scm_equal(scm_eval("exercise2-57.rkt", "(make-product 1 2)"), "2"), "(make-product 1 2) is 2");
ok(scm_equal(scm_eval("exercise2-57.rkt", "(make-product 'x 1)"), "'x"), "(make-product 'x 1) is 'x");
ok(scm_equal(scm_eval("exercise2-57.rkt", "(make-product 1 'x)"), "'x"), "(make-product 1 'x) is 'x");
ok(scm_equal(scm_eval("exercise2-57.rkt", "(make-product 'x)"), "'x"), "(make-product 'x) is 'x");
ok(scm_equal(scm_eval("exercise2-57.rkt", "(make-product 'x 'y 'z)"), "'(* x y z)"), "(make-product 'x 'y 'z) is '(* x y z)");

ok(scm_equal(scm_eval("exercise2-57.rkt", "(multiplier '(* x 3))"), "'x"), "(multiplier '(* x 3)) is 'x");
ok(scm_equal(scm_eval("exercise2-57.rkt", "(multiplicand '(* x 3))"), "3"), "(multiplicand '(* x 3)) is 3");
ok(scm_equal(scm_eval("exercise2-57.rkt", "(multiplier '(* x y z))"), "'x"), "(multiplier '(* x y z)) is 'x");
ok(scm_equal(scm_eval("exercise2-57.rkt", "(multiplicand '(* x y z))"), "'(* y z)"), "(multiplicand '(* x y z)) is '(* y z)");

ok(scm_equal(scm_eval("exercise2-57.rkt", "(multiplicand equation1)"), "'(* y (+ x 3))"), "(multiplicand equation1) is correct");
ok(scm_equal(scm_eval("exercise2-57.rkt", "(deriv equation1 'x)"), "'(+ (* x y) (* y (+ x 3)))"), "(deriv equation1 'x) is correct");

ok(scm_equal(scm_eval("exercises.rkt", "(accumulate-n + 0 (list (list 1 2 3) (list 4 5 6) (list 7 8 9) (list 10 11 12)))"), "'(22 26 30)"), "(accumulate-n + 0 (list (list 1 2 3) (list 4 5 6) (list 7 8 9) (list 10 11 12)))");
ok(scm_equal(scm_eval("exercises.rkt", "p2_1"), '#t'), "p2_1");
ok(scm_equal(scm_eval("exercises.rkt", "p2_2"), '#t'), "p2_2");
ok(scm_equal(scm_eval("exercises.rkt", "p2_3"), '#t'), "p2_3");
ok(scm_equal(scm_eval("exercises.rkt", "p2_4"), '#t'), "p2_4");
ok(scm_equal(scm_eval("exercises.rkt", "p2_5"), '#t'), "p2_5");
ok(scm_equal(scm_eval("exercises.rkt", "p2_6"), '#t'), "p2_6");
ok(scm_equal(scm_eval("exercises.rkt", "p2_7"), '#t'), "p2_7");
ok(scm_equal(scm_eval("exercises.rkt", "(my-equal? '(this is a list) '(this is a list))"), "#t"), "(my-equal? '(this is a list) '(this is a list))");
ok(scm_equal(scm_eval("exercises.rkt", "(my-equal? '(this is a list) '(this (is a) list))"), "#f"), "(my-equal? '(this is a list) '(this (is a) list))");
ok(scm_equal(scm_eval("exercises.rkt", "(my-equal? '(1 (2 3) 4) '(1 (2 3) 4))"), "#t"), "(my-equal? '(1 (2 3) 4) '(1 (2 3) 4))");
ok(scm_equal(scm_eval("exercises.rkt", "(my-equal? 'a 'b)"), "#f"), "(my-equal? 'a 'b)");
ok(scm_equal(scm_eval("exercises.rkt", "(my-equal? 'app 'app)"), "#t"), "(my-equal? 'app 'app)");
ok(scm_equal(scm_eval("exercises.rkt", "p4"), '#t'), "p4");
