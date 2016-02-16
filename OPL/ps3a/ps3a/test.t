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
    copy("ps3a.rkt", $tmpcode) or die "Copy failed: $!";
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

use Test::Simple tests => 17;

ok(scm_equal(scm_eval("list5flag"), "#t"), "list5");
ok(scm_equal(scm_eval("list6flag"), "#t"), "list6");
ok(scm_equal(scm_eval("list7flag"), "#t"), "list7");
ok(scm_equal(scm_eval("list8flag"), "#t"), "list8");

ok(scm_equal(scm_eval("(sum-list-r '(1 2 3))"), 6), "(sum-list-r '(1 2 3)) is 6");
ok(scm_equal(scm_eval("(sum-list-r '())"), 0), "(sum-list-r '()) is 0");
ok(scm_equal(scm_eval("(sum-list-i '(1 2 3))"), 6), "(sum-list-i '(1 2 3)) is 6");
ok(scm_equal(scm_eval("(sum-list-i '())"), 0), "(sum-list-i '()) is 0");

ok(scm_equal(scm_eval("lpa"), '#t'), "list-prod number of recursions -- recursive proc");
ok(scm_equal(scm_eval("lpa"), '#t'), "list-prod recursive proc -- space and time");
ok(scm_equal(scm_eval("(list-prod-iter '(1 2 3 4))"), 24), "(list-prod-iter '(1 2 3 4))");
ok(scm_equal(scm_eval("lpd"), '#t'), "list-prod iterative proc -- space and time");

ok(scm_equal(scm_eval("(sum-of-prods '())"), 0), "(sum-of-prods '()) is 0");
ok(scm_equal(scm_eval("(sum-of-prods '(1 2 3 4 5 6))"), 44), "(sum-of-prods '(1 2 3 4 5 6)) is 44");
ok(scm_equal(scm_eval("(sum-of-prods '(34 73 18 99 12 12 44 31))"), 5772), "(sum-of-prods '(34 73 18 99 12 12 44 31) is 5772");

ok(scm_equal(scm_eval("(same-parity 1 2 3 4 5 6 7)"), "'(1 3 5 7)"), "(same-parity 1 2 3 4 5 6 7)");
ok(scm_equal(scm_eval("(same-parity 2 3 4 5 6 7)"), "'(2 4 6)"), "(same-parity 2 3 4 5 6 7)");
