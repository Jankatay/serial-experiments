#!/usr/bin/env perl

use warnings;
use strict;

print("Content-type: video/mp4\n");
print("Content-Disposition: attachment\n\n"); 

my $filename = "./video.mp4";
open(FH, '<', $filename) or die $!;
while(<FH>) { print $_; }
close(FH);

