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
    copy("ps1.rkt", $tmpcode) or die "Copy failed: $!";
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

use Test::Simple tests => 30;

ok(scm_equal(scm_eval("(square 3)"), 9), "(square 3)");
ok(scm_equal(scm_eval("(square 1)"), 1), "(square 1)");
ok(scm_equal(scm_eval("(abs-using-if 0)"), 0), "(abs-using-if 0)");
ok(scm_equal(scm_eval("(abs-using-if 1)"), 1), "(abs-using-if 1)");
ok(scm_equal(scm_eval("(abs-using-if -3)"), 3), "(abs-using-if -3)");
ok(scm_equal(scm_eval("(abs-using-cond 0)"), 0), "(abs-using-cond 0)");
ok(scm_equal(scm_eval("(abs-using-cond 1)"), 1), "(abs-using-cond 1)");
ok(scm_equal(scm_eval("(abs-using-cond -3)"), 3), "(abs-using-cond -3)");
ok(scm_equal(scm_eval("(fact 1)"), 1), "(fact 1)");
ok(scm_equal(scm_eval("(fact 5)"), 120), "(fact 5)");
ok(scm_equal(scm_eval("(fact 20)"), 2432902008176640000), "(fact 20)");
ok(scm_equal(scm_eval("(comb 3 2)"), 3), "(comb 3 2)");
ok(scm_equal(scm_eval("(comb 4 2)"), 6), "(comb 4 2)");
ok(scm_equal(scm_eval("(comb 10 2)"), 45), "(comb 10 2)");
ok(scm_equal(scm_eval("(comb 93 37)"), '118206769052646517220135262'), "(comb 93 37)");
ok(scm_equal(scm_eval("(triple 0)"), 0), "(triple 0)");
ok(scm_equal(scm_eval("(triple 5)"), 15), "(triple 15)");
ok(scm_equal(scm_eval("(triple -1)"), -3), "(triple -1)");
ok(scm_equal(scm_eval("(diff-of-triples 1 0)"), 3), "(diff-of-triples 1 0)");
ok(scm_equal(scm_eval("(diff-of-triples 3 1)"), 6), "(diff-of-triples 3 1)");
ok(scm_equal(scm_eval("(diff-of-triples 10 2)"), 24), "(diff-of-triples 10 2)");
ok(scm_equal(scm_eval("(smallest-of-three 1 2 3)"), 1), "(smallest-of-three 1 2 3)");
ok(scm_equal(scm_eval("(smallest-of-three 2 1 3)"), 1), "(smallest-of-three 2 1 3)");
ok(scm_equal(scm_eval("(smallest-of-three 3 2 1)"), 1), "(smallest-of-three 3 2 1)");
ok(scm_equal(scm_eval("(smallest-of-three 1 1 2)"), 1), "(smallest-of-three 1 1 2)");
ok(scm_equal(scm_eval("(smallest-of-three -1 -1 0)"), -1), "(smallest-of-three -1 -1 0)");
ok(scm_equal(scm_eval("(smallest-of-three 1 1 1)"), 1), "(smallest-of-three 1 1 1)");
ok(scm_equal(scm_eval("(smallest-tripled 1 2 3)"), 3), "(smallest-tripled 1 2 3)");
ok(scm_equal(scm_eval("(smallest-tripled -1 -1 0)"), -3), "(smallest-tripled -1 -1 0)");
ok(scm_equal(scm_eval("(smallest-tripled 30 20 10)"), 30), "(smallest-tripled 30 20 10)");
