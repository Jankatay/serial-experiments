#!/usr/bin/env perl

use warnings;
use strict;

# HTTP headers
my $boundary = "Ucmd3AW\$|o-!2.<-<!:<~~-`ST-98o+-}`o-%[2ix-|\$nA\"-:yx?";
print "Content-type: video/mp4\r\n";
print "Content-Disposition: attachment\r\n";
print "Content-Type: multipart/form-data; boundary=$boundary\r\n\r\n";


# get user input 
print {*STDERR} "Enter link: ";
my $link = <STDIN>;

# download 
open(my $pipe_fh, "-|", "yt-dlp -t mp4 -o - $link --no-exec");

# write to output as it downloads with seperators
my $buf = "";
while(sysread($pipe_fh, $buf, 512) != 0) {
  print("\r\n--$boundary\nContent-Type: video/mp4\r\n\r\n$buf");
} print("\r\n--$boundary--"); # finish
