/**********************************************************************
 *  readme.txt template
 *  Kronos PS7a startup
 **********************************************************************/

Name: Jason Downing
Hours to complete assignment (optional): 5 - 6 hours, plus fighting with Bottlenose.

/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not?
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/

Yup. I can detect successful boots, count lines, calculate time differences
and output all this to a file with the right extension.

/**********************************************************************
 *  Copy here all regex's you created for parsing the file,
 *  and explain individually what each ones does.
 **********************************************************************/

std::string start_string = "([0-9]{4})-([0-9]{2})-([0-9]{2}) ";
start_string += "([0-9]{2}):([0-9]{2}):([0-9]{2}): \\(log.c.166\\) ";
start_string += "server started";

This my regex to detect the boot statement. It finds a matching line with
a time stamp, following by the words "(log.c.166) server started". Matching
the regex against this whole statement made it easy to pull the date and
time from the current line.

std::string end_string = "([0-9]{4})-([0-9]{2})-([0-9]{2}) ";
end_string += "([0-9]{2}):([0-9]{2}):([0-9]{2}).([0-9]{3}):INFO:oejs.";
end_string += "AbstractConnector:Started SelectChannelConnector@0.0.0.0:9080";

I used this regex to find a succesful boot. A successful boot is marked by
a time stamp, followed by the string:
"INFO:oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:9080".
As with the boot statement, I pulled the date / time from the smatch variable
that I passed to the regex search / match methods.

/**********************************************************************
 *  Describe your overall approach for solving the problem.
 *  100-200 words.
 **********************************************************************/
I pretty much saw this problem as being an issue of using the regex to
detect the line for booting and for a successful boot. Then you can grab
the date / time from the smatch variable that I passed to boost's regex search
and match methods.

I also used a boolean to keep track of the last time I've
seen a boot statement - if I found another boot statement and the bool for
spotting boot statements was true, then we've got an unsuccessful boot since
we never saw a success statement and flipped the bool to false.

I also found it helpful to write everything into a string, so I could easily
dump the report string to either standard I/O and a file.

The date / time calculations were a pain to figure out but in the end doing
the long way of creating a gregorian object, and using that to create a ptime
object seemed to work.


/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/
Mostly stuff from the boost docs helped, as well as from the lecture
capture.

This saved the day:
http://www.cplusplus.com/reference/string/string/pop_back/

/**********************************************************************
 *  Describe any serious problems you encountered.
 **********************************************************************/
I had trouble getting date and time to work, ptime was kinda funky
and wouldn't take my date/time string and kept complaining about an
invalid month day. I redid my approach and did it the long way like
described in lecture and it worked fine.

/**********************************************************************
 *  List any other comments here.
 **********************************************************************/
N/A

