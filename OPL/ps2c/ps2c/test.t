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
    copy("ps2c.rkt", $tmpcode) or die "Copy failed: $!";
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

use Test::Simple tests => 16;

#ok(scm_equal(scm_eval("(+ 1 1)"), 2), "1 + 1 is 2");

# points
ok(scm_equal(scm_eval("(x-point (make-point 10 30))"), 10), "x-point selector");
ok(scm_equal(scm_eval("(y-point (make-point 10 30))"), 30), "y-point selector");

# segments
ok(scm_equal(scm_eval("(x-point (start-seg (make-seg (make-point 0 0) (make-point 40 50))))"), 0), "x-point of start-seg of make-seg");
ok(scm_equal(scm_eval("(y-point (end-seg (make-seg (make-point 0 0) (make-point 40 50))))"), 50), "y-point of end-seg of make-seg");
ok(scm_equal(scm_eval("(x-point (midpoint-seg (make-seg (make-point 0 0) (make-point 40 50))))"), 20), "x-point of midpoint-seg of make-seg");
ok(scm_equal(scm_eval("(y-point (midpoint-seg (make-seg (make-point 0 0) (make-point 40 50))))"), 25), "y-point of midpoint-seg of make-seg");

# rectangles
ok(scm_equal(scm_eval("(width (make-rect 0 0 100 50))"), 100), "width of (make-rect 0 0 100 50) is 100");
ok(scm_equal(scm_eval("(width (make-rect 100 50 0 0))"), 100), "width of (make-rect 100 50 0 0) is 100");
ok(scm_equal(scm_eval("(height (make-rect 0 0 100 50))"), 50), "height of (make-rect 0 0 100 50) is 50");
ok(scm_equal(scm_eval("(height (make-rect 100 50 0 0))"), 50), "height of (make-rect 100 50 0 0) is 50");
ok(scm_equal(scm_eval("(area (make-rect 0 0 100 50))"), 5000), "area of (make-rect 0 0 100 50) is 5000");
ok(scm_equal(scm_eval("(area (make-rect 100 50 0 0))"), 5000), "area of (make-rect 100 50 0 0) is 5000");
ok(scm_equal(scm_eval("(perimeter (make-rect 0 0 100 50))"), 300), "perimeter of (make-rect 0 0 100 50) is 300");
ok(scm_equal(scm_eval("(perimeter (make-rect 100 50 0 0))"), 300), "perimeter of (make-rect 100 50 0 0) is 300");

# using procedure closures to implement cons cells
ok(scm_equal(scm_eval("(my-cdr (my-cons 'foo 'bar))"), "'bar"), "my-cdr test 1");
ok(scm_equal(scm_eval("(my-cdr (my-cons (+ 1 2) (+ 3 4)))"), 7), "my-cdr test 2");
# ok(scm_equal(scm_eval("p4"), '#t'), "p5");
# ok(scm_equal(scm_eval("(my-length '(1 2 3 4))"), 4), "(my-length '(1 2 3 4))");
# ok(scm_equal(scm_eval("(count-leaves '(1 (2 3) 4 (5 6)))"), 6), "(count-leaves '(1 (2 3) 4 (5 6)))");
