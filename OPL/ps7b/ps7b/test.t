#!/usr/bin/perl
use 5.10.0;
use warnings FATAL => 'all';

use File::Temp;
use File::Copy;
use IO::Handle;

# have to concatenate the command line after the source file
sub scm_eval {
    my ($cmdline) = @_;
    my $tmpcode = File::Temp->new;
    copy("mceval-with-let.ss", $tmpcode) or die "Copy failed: $!";
    open(my $fh, '>>', $tmpcode);
    $fh->say("\n"); 
    $fh->say($cmdline);
    my $result = `plt-r5rs $tmpcode`;
    chomp $result;
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

use Test::Simple tests => 5;

#ok(scm_equal(scm_eval("(+ 1 1)"), "2"), "sanity check")
#ok(scm_equal(scm_eval("(mc-eval '(uml:+ 1 1) the-global-environment)"), "2"), "(uml:+ 1 1) is 2");
ok(scm_equal(scm_eval("(mc-eval '(uml:begin (uml:define n 0) (uml:for (i 1 3) (uml:set! n (uml:+ n i))) n) the-global-environment)"), "6"), "uml:for -- loop from 1 to 3");
ok(scm_equal(scm_eval("(mc-eval '(uml:begin (uml:define n 0) (uml:for (i 1 1) (uml:set! n (uml:+ n i))) n) the-global-environment)"), "1"), "uml:for -- loop from 1 to 1 (should run once)");
ok(scm_equal(scm_eval("(mc-eval '(uml:begin (uml:define n 0) (uml:for (i -5 10) (uml:set! n (uml:+ n i))) n) the-global-environment)"), "40"), "uml:for -- loop from -5 to 10");
ok(scm_equal(scm_eval("(mc-eval '(uml:begin (uml:define n 0) (uml:for (i 1 (uml:+ 1 2)) (uml:set! n (uml:+ n i))) n) the-global-environment)"), "6"), "uml:for -- loop from 1 to (+ 1 2)");
ok(scm_equal(scm_eval("(mc-eval '(uml:begin (uml:define n 0) (uml:for (i (uml:+ 1 0) 3) (uml:set! n (uml:+ n i))) n) the-global-environment)"), "6"), "uml:for -- loop from (+ 1 0) 3");

