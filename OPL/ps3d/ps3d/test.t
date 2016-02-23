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
    copy("ps3d.rkt", $tmpcode) or die "Copy failed: $!";
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

use Test::Simple tests => 17;

ok(scm_equal(scm_eval("(count-leaves test-tree)"), 7), "(count-leaves test-tree)");
ok(scm_equal(scm_eval("(sum-leaves test-tree)"), 28), "(sum-leaves test-tree)");
ok(scm_equal(scm_eval("(triple-leaves test-tree)"), "'(3 (6 (9 (12) 15) 18) 21)"), "(triple-leaves test-tree)");
ok(scm_equal(scm_eval("(count-leaves-with-map '(1 2 3 4 5 6))"), 6), "(count-leaves-with-map '(1 2 3 4 5 6))");
ok(scm_equal(scm_eval("(count-leaves-with-map '(1 (2 3) 4 (5 6)))"), 6), "(count-leaves-with-map '(1 (2 3) 4 (5 6)))");
ok(scm_equal(scm_eval("(flip-cons 'a 'b)"), "'(b . a)"), "(flip-cons 'a 'b)");
ok(scm_equal(scm_eval("(flip-minus 5 6)"), 1), "(flip-minus 5 6)");
ok(scm_equal(scm_eval("(flip-odd 5)"), '#t'), "(flip-odd 5)");
ok(scm_equal(scm_eval("(flip-odd 4)"), '#f'), "(flip-odd 4)");
ok(scm_equal(scm_eval("(fold-right / 1 (list 1 2 3))"), '3/2'), "(fold-right / 1 (list 1 2 3))");
ok(scm_equal(scm_eval("(fold-right list nil (list 1 2 3))"), "'(1 (2 (3 ())))"), "(fold-right list nil (list 1 2 3))");
ok(scm_equal(scm_eval("p4"), '#t'), "p4");
ok(scm_equal(scm_eval("(bucket '())"), "'()"), "(bucket '())");
ok(scm_equal(scm_eval("(bucket '(1))"), "'((1))"), "(bucket '(1))");
ok(scm_equal(scm_eval("(bucket '(1 1))"), "'((1 1))"), "(bucket '(1 1))");
ok(scm_equal(scm_eval("(bucket '(1 2 3 4 5))"), "'((1) (2) (3) (4) (5))"), "(bucket '(1 2 3 4 5))");
ok(scm_equal(scm_eval("(bucket '(1 1 2 2 2 3 1 1 1 2 3 3))"), "'((1 1) (2 2 2) (3) (1 1 1) (2) (3 3))"), "(bucket '(1 1 2 2 2 3 1 1 1 2 3 3))");
