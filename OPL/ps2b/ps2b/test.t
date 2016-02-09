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
    copy("ps2b.rkt", $tmpcode) or die "Copy failed: $!";
    open(my $fh, '>>', $tmpcode);
    $fh->say('(define-namespace-anchor bottlenose-nsa)
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

use Test::Simple tests => 22;

ok(scm_equal(scm_eval("(sum square 2 inc 4)"), 29), "(sum square 2 inc 4) is 29");
ok(scm_equal(scm_eval("(sum square 2 inc 2)"), 4), "(sum square 2 inc 2) is 4");
ok(scm_equal(scm_eval("(* (product1 pi-term 1 next 6) 4)"), '4096/1225'), "(* (product1 pi-term 1 next 6) 4) is 4096/1225");
ok(scm_equal(scm_eval("(product2 pi-term 1 next 6)"), '1024/1225'), "(product2 pi-term 1 next 6) is 1024/1225");
ok(scm_equal(scm_eval("(sum1 square 2 inc 4)"), 29), "(sum square 2 inc 4) is 29");
ok(scm_equal(scm_eval("(* (product pi-term 1 next 6) 4)"), '4096/1225'), "(* (product pi-term 1 next 6) 4) is 4096/1225");
ok(scm_equal(scm_eval("((double inc) 3)"), 5), "((double inc) 3) is 5");
ok(scm_equal(scm_eval("(((double double) inc) 3)"), 7), "(((double double) inc) 3) is 7");
ok(scm_equal(scm_eval("(((double (double double)) inc) 5)"), 21), "(((double (double double)) inc) 5) is 21");
ok(scm_equal(scm_eval("((compose inc square) 6)"), 37), "((compose inc square) 6) is 37");
ok(scm_equal(scm_eval("((compose square inc) 6)"), 49), "((compose square inc) 6) is 49");
ok(scm_equal(scm_eval("((compose (compose square square) square) 2)"), 256), "((compose (compose square square) square) 2) is 256");
ok(scm_equal(scm_eval("((expnt-iter 0) 10)"), 1), "((expnt-iter 0) 10) is 1");
ok(scm_equal(scm_eval("((expnt-iter 1) 10)"), 10), "((expnt-iter 1) 10) is 10");
ok(scm_equal(scm_eval("((expnt-iter 2) 10)"), 100), "((expnt-iter 2) 10) is 100");
ok(scm_equal(scm_eval("((expnt-iter 100) 10)"), "(expt 10 100)"), "((expnt-iter 100) 10) is 10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

ok(scm_equal(scm_eval("(proc1 3 4)"), 50), "(proc1 3 4) is 50");
ok(scm_equal(scm_eval("(proc2 5)"), 336), "(proc2 5) is 336");
ok(scm_equal(scm_eval("(proc3 6)"), 21), "(proc3 6) is 21");
ok(scm_equal(scm_eval("(proc4 5 12)"), 45), "(proc4 5 12) is 45");
ok(scm_equal(scm_eval("(proc5 10)"), 114), "(proc5 10) is 114");
ok(scm_equal(scm_eval("(proc6 10 20 30)"), 1500), "(proc6 10 20 30) is 1500");

#ok(scm_equal(scm_eval("((repeat square 2) 5)"), 625), "((repeat square 2) 5) is 625");
