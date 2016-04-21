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
    copy("ps8.rkt", $tmpcode) or die "Copy failed: $!";
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

use Test::Simple tests => 25;

ok(scm_equal(scm_eval("(begin (define foo (stream-enumerate-interval 32 40)) (stream-ref (convert-temps foo) 0))"), 0), "conv-temps of 32");
ok(scm_equal(scm_eval("(begin (define foo (stream-enumerate-interval 32 40)) (stream-ref (convert-temps foo) 1))"), "(/ 5 9)"), "conv-temps of 33");
ok(scm_equal(scm_eval("(begin (define foo (stream-enumerate-interval 32 40)) (stream-ref (convert-temps foo) 5))"), "(/ 25 9)"), "conv-temps of 37");
ok(scm_equal(scm_eval("(begin (define foo (stream-enumerate-interval 32 40)) (stream-ref (convert-temps foo) 8))"), "(/ 40 9)"), "conv-temps of 40");

ok(scm_equal(scm_eval("(stream-ref (divisible-by-2-3-5 integers) 0)"), 2), "first item of (divisible-by-2-3-5 integers) is 2");
ok(scm_equal(scm_eval("(stream-ref (divisible-by-2-3-5 integers) 1)"), 3), "second item of (divisible-by-2-3-5 integers) is 3");
ok(scm_equal(scm_eval("(stream-ref (divisible-by-2-3-5 integers) 2)"), 4), "third item of (divisible-by-2-3-5 integers) is 4");
ok(scm_equal(scm_eval("(stream-ref (divisible-by-2-3-5 integers) 3)"), 5), "fourth item of (divisible-by-2-3-5 integers) is 5");
ok(scm_equal(scm_eval("(stream-ref (divisible-by-2-3-5 integers) 1000)"), 1365), "1001st item of (divisible-by-2-3-5 integers) is 1365");

ok(scm_equal(scm_eval("(stream-ref my-integers 0)"), 1), "first item of my-integers is 1");
ok(scm_equal(scm_eval("(stream-ref my-integers 4)"), 5), "fifth item of my-integers is 5");
ok(scm_equal(scm_eval("(stream-ref my-integers 1000)"), 1001), "1001st item of my-integers is 1001");

ok(scm_equal(scm_eval("p4_1"), "#t"), "problem 4 part 1 answered");
ok(scm_equal(scm_eval("p4_2"), "#t"), "problem 4 part 2 answered");
ok(scm_equal(scm_eval("p4_3"), "#t"), "problem 4 part 3 answered");

# ok(scm_equal(scm_eval("p5"), "#t"), "problem 5 answered");
# ok(scm_equal(scm_eval("p5"), "#t"), "problem 5 answered");
# ok(scm_equal(scm_eval("p5"), "#t"), "problem 5 answered");
# ok(scm_equal(scm_eval("p5"), "#t"), "problem 5 answered");

ok(scm_equal(scm_eval("p6"), "#t"), "problem 6 answered");
ok(scm_equal(scm_eval("p6"), "#t"), "problem 6 answered");
ok(scm_equal(scm_eval("p6"), "#t"), "problem 6 answered");

ok(scm_equal(scm_eval("(stream-ref (mul-streams integers integers) 0)"), 1), "mul-streams first elements product");
ok(scm_equal(scm_eval("(stream-ref (mul-streams integers integers) 99)"), 10000), "mul-streams hundredth elements product");

ok(scm_equal(scm_eval("(stream-ref factorials 0)"), 1), "factorial of 0 is 1");
ok(scm_equal(scm_eval("(stream-ref factorials 1)"), 1), "factorial of 1 is 1");
ok(scm_equal(scm_eval("(stream-ref factorials 2)"), 2), "factorial of 2 is 2");
ok(scm_equal(scm_eval("(stream-ref factorials 3)"), 6), "factorial of 3 is 6");
ok(scm_equal(scm_eval("(stream-ref factorials 10)"), 3628800), "factorial of 10 is 3628800");

# ok(scm_equal(scm_eval("p8_1"), "#t"), "problem 8 part 1 answered");
# ok(scm_equal(scm_eval("p8_1"), "#t"), "problem 8 part 1 answered");
# ok(scm_equal(scm_eval("p8_2"), "#t"), "problem 8 part 2 answered");
# ok(scm_equal(scm_eval("p8_2"), "#t"), "problem 8 part 2 answered");
