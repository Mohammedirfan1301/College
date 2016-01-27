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
    copy("ps2a.rkt", $tmpcode) or die "Copy failed: $!";
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

use Test::Simple tests => 37;

ok(scm_equal(scm_eval("(sum-recursive 2)"), 3), "(sum-recursive 2) is 3");
ok(scm_equal(scm_eval("(sum-recursive 10)"), 55), "(sum-recursive 10) is 55");
ok(scm_equal(scm_eval("(sum-recursive 99)"), 4950), "(sum-recursive 99) is 4950");

ok(scm_equal(scm_eval("(sum-iterative 2)"), 3), "(sum-iterative 2) is 3");
ok(scm_equal(scm_eval("(sum-iterative 50)"), 1275), "(sum-iterative 50) is 1275");
ok(scm_equal(scm_eval("(sum-iterative 1000000)"), 500000500000), "(sum-iterative 1000000) is 500000500000");

ok(scm_equal(scm_eval("(sum-squares-recursive 2)"), 5), "(sum-squares-recursive 2) is 5");
ok(scm_equal(scm_eval("(sum-squares-recursive 10)"), 385), "(sum-squares-recursive 10) is 385");
ok(scm_equal(scm_eval("(sum-squares-recursive 100)"), 338350), "(sum-squares-recursive 100) is 338350");

ok(scm_equal(scm_eval("(sum-squares-iterative 2)"), 5), "(sum-squares-iterative 2) is 5");
ok(scm_equal(scm_eval("(sum-squares-iterative 50)"), 42925), "(sum-squares-iterative 50) is 42925");
ok(scm_equal(scm_eval("(sum-squares-iterative 1000000)"), 333333833333500000), "(sum-squares-iterative 1000000) is 333333833333500000");

ok(scm_equal(scm_eval("(sum-alt-squares-recursive 2)"), 10), "(sum-alt-squares-recursive 2) is 10");
ok(scm_equal(scm_eval("(sum-alt-squares-recursive 10)"), 1330), "(sum-alt-squares-recursive 10) is 1330");
ok(scm_equal(scm_eval("(sum-alt-squares-recursive 100)"), 1333300), "(sum-alt-squares-recursive 100) is 1333300");

ok(scm_equal(scm_eval("(sum-alt-squares-iterative 2)"), 10), "(sum-alt-squares-iterative 2) is 10");
ok(scm_equal(scm_eval("(sum-alt-squares-iterative 40)"), 85320), "(sum-alt-squares-iterative 40) is 85320");
ok(scm_equal(scm_eval("(sum-alt-squares-iterative 1000000)"), 1333333333333000000), "(sum-alt-squares-iterative 1000000) is 1333333333333000000");

ok(scm_equal(scm_eval("(two-thirds-series-r 2)"), "(/ 3 4)"), "(two-thirds-series-r 2) is 3/4");
ok(scm_equal(scm_eval("(two-thirds-series-r 5)"), "(/ 21 32)"), "(two-thirds-series-r 5) is 21/32");
ok(scm_equal(scm_eval("(two-thirds-series-r 10)"), "(/ 683 1024)"), "(two-thirds-series-r 10) is 683/1024");

ok(scm_equal(scm_eval("(two-thirds-series-i 2)"), "(/ 3 4)"), "(two-thirds-series-i 2) is 3/4");
ok(scm_equal(scm_eval("(two-thirds-series-i 5)"), "(/ 21 32)"), "(two-thirds-series-i 5) is 21/32");
ok(scm_equal(scm_eval("(two-thirds-series-i 100)"), "(/ 845100400152152934331135470251 1267650600228229401496703205376)"), "(two-thirds-series-i 100) is 845100400152152934331135470251/1267650600228229401496703205376");

ok(scm_equal(scm_eval("(f-recursive 2)"), 2), "(f-recursive 2)");
ok(scm_equal(scm_eval("(f-recursive 3)"), 4), "(f-recursive 3)");
ok(scm_equal(scm_eval("(f-recursive 4)"), 11), "(f-recursive 4)");

ok(scm_equal(scm_eval("tail-recursion"), '#t'), "tail-recursion");
ok(scm_equal(scm_eval("tail-recursion"), '#t'), "tail-recursion");
ok(scm_equal(scm_eval("tail-recursion"), '#t'), "tail-recursion");
ok(scm_equal(scm_eval("tail-recursion"), '#t'), "tail-recursion");
ok(scm_equal(scm_eval("tail-recursion"), '#t'), "tail-recursion");

ok(scm_equal(scm_eval("(fast-expt 2 0)"), 1), "(fast-expt 2 0)");
ok(scm_equal(scm_eval("(fast-expt 2 1)"), 2), "(fast-expt 2 1)");
ok(scm_equal(scm_eval("(fast-expt 2 2)"), 4), "(fast-expt 2 2)");
ok(scm_equal(scm_eval("(fast-expt 2 3)"), 8), "(fast-expt 2 3)");
ok(scm_equal(scm_eval("(fast-expt 2 5)"), 32), "(fast-expt 2 5)");


