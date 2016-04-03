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
    copy("ps6.rkt", $tmpcode) or die "Copy failed: $!";
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

use Test::Simple tests => 20;

#ok(scm_equal(scm_eval("(+ 1 1)"), "2"), "sanity check");

# exercise 3.1
ok(scm_equal(scm_eval("(begin (define a (make-accumulator 5)) (a 10))"), "15"), "make-accumulator test 1");
ok(scm_equal(scm_eval("(begin (define a (make-accumulator 5)) (a 10) (a 10))"), "25"), "make-accumulator test 2");
ok(scm_equal(scm_eval("exercise-3.1-env"), "#t"), "ex 3.1 env diagram");
ok(scm_equal(scm_eval("exercise-3.1-env"), "#t"), "ex 3.1 env diagram");

# exercise 3.2
ok(scm_equal(scm_eval("(begin (define s (make-monitored (lambda (n) (* n n)))) (s 10))"), "100"), "make-monitored function test");
ok(scm_equal(scm_eval("(begin (define s (make-monitored (lambda (n) (* n n)))) (s 'how-many-calls?))"), "0"), "make-monitored count is 0");
ok(scm_equal(scm_eval("(begin (define s (make-monitored (lambda (n) (* n n)))) (s 10) (s 'how-many-calls?))"), "1"), "make-monitored count is 1");
ok(scm_equal(scm_eval("(begin (define s (make-monitored (lambda (n) (* n n)))) (s 10) (s 10) (s 'how-many-calls?))"), "2"), "make-monitored count is 2");
ok(scm_equal(scm_eval("exercise-3.2-env"), "#t"), "ex 3.2 env diagram");
ok(scm_equal(scm_eval("exercise-3.2-env"), "#t"), "ex 3.2 env diagram");

# exercise 3.3
ok(scm_equal(scm_eval("(begin (define acc (make-account 100 'foo)) ((acc 'foo 'deposit) 10))"), "110"), "make-account deposit");
ok(scm_equal(scm_eval("(begin (define acc (make-account 100 'foo)) ((acc 'foo 'withdraw) 10))"), "90"), "make-account withdraw");
ok(scm_equal(scm_eval("(begin (define acc (make-account 100 'foo)) ((acc 'foo 'withdraw) 10) ((acc 'foo 'withdraw) 10) ((acc 'foo 'withdraw) 10) ((acc 'foo 'deposit) 50))"), "120"), "make-account multiple withdraw and deposit");
ok(scm_equal(scm_eval("(begin (define acc (make-account 100 'foo)) ((acc 'bar 'deposit) 10))"), '"Incorrect password"'), "make-account bad password");

# exercise 3.4
ok(scm_equal(scm_eval("(begin (define acc (make-account-secure 100 'foo)) ((acc 'foo 'withdraw) 10) )"), "90"), "make-account-secure -- one withdraw");
ok(scm_equal(scm_eval("(begin (define acc (make-account-secure 100 'foo)) (for ((i '(1 2 3 4 5 6))) ((acc 'foo 'withdraw) 10)) ((acc 'foo 'withdraw) 10) )"), "30"), "make-account-secure -- 7 withdraws");
ok(scm_equal(scm_eval("(begin (define acc (make-account-secure 100 'foo)) (for ((i '(1 2 3 4 5 6 7))) ((acc 'bar 'withdraw) 10)) ((acc 'foo 'withdraw) 10) )"), "90"), "make-account-secure -- 7 password fails then successful withdraw");
ok(scm_equal(scm_eval("(begin (define acc (make-account-secure 100 'foo)) (for ((i '(1 2 3 4 5 6 7))) ((acc 'bar 'withdraw) 10)) ((acc 'bar 'withdraw) 10) )"), '"your account has been locked. please call customer service."'), "make-account-secure -- 8 password fails gets lockout");
ok(scm_equal(scm_eval("(begin (define acc (make-account-secure 100 'foo)) (for ((i '(1 2 3 4 5 6 7 8))) ((acc 'bar 'withdraw) 10)) ((acc 'foo 'withdraw) 10) )"), '"your account has been locked. please call customer service."'), "make-account-secure -- after lockout, can't withdraw");
ok(scm_equal(scm_eval("(begin (define acc (make-account-secure 100 'foo)) (for ((i '(1 2 3 4 5 6 7 8))) ((acc 'bar 'withdraw) 10)) ((acc 'foo 'deposit) 10) )"), '"your account has been locked. please call customer service."'), "make-account-secure -- after lockout, can't deposit");


