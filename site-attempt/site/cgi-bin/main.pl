#!/usr/bin/env perl

# only default imports
use Symbol;
use warnings;
use strict;
use IPC::Open3;

# get user input 
my $link = "https://www.youtube.com/watch?v=tPEE9ZwT";

# set immediate-flush for the outputs
$| = 1;

# start downloading the data
#chdir "/tmp/"; # yt-dlp requires write permissions to working directory even if not writing anything
my $cmd = "yt-dlp -q -t mp4 --max-filesize 50M --no-continue $link --no-exec -o - 2>/dev/null";
open(my $download, $cmd);

# make sure you are the 

# HTTP download headers
print "Content-Encoding: chunked\r\n";
print "Content-type: video/mp4\r\n";
print "Content-Disposition: attachment\r\n\r\n";

# send to client as it downloads, 512 bytes at a time
while(sysread($download, my $buf, 512) > 0) {
  print "$buf";
}




