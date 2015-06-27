# cpp_socks
C++ socket library - uses the same interface as standard &lt;iostream>.

The sample server implementation is in `server.cpp` file. To test how it works, you might issue following commands:
```
$ make
$ bin/server 8888
$ # In other terminal:
$ nc localhost 8888
Hello there! Type two integers now.
> 3 5
Thanks. Here is their sum: 8
Now I'll just echo your line of text.
> Hmmm, it works.
Hmmm, it works.
```



This library was inspired by http://www.pcs.cnu.edu/~dgame/sockets/socketsC++/sockets.html

I decided to recreate it in a better way though, because the original one had some flaws, such as not
being able to specify a timeout, or not parsing anything correctly if the message comes in two parts (see below
for explanation):

Remote wants to send "123 456\n":
```
+-+-+-+-+-+-+-+--+
|1|2|3| |4|5|6|\n|
+-+-+-+-+-+-+-+--+
```
But it turns out  being split:
```
+-+-+-+  +-+-+-+  +-+--+
|1|2|3|  | |4|5|  |6|\n|
+-+-+-+  +-+-+-+  +-+--+
```
(the OS arranges packets, so it's independent from library)

Say host wanted to input two numbers:
```
int a,b;
in>>a>>b;
```
The original library would read the ementioned packets as:
```
a=123;
b=45;
```
and leave the "6\n" in buffer for next reads.
This library reads it corrrectly:
```
a=123;
b=456;
```
You can check this using the following snippet of Python code:
```
import sys
import time

# Printing one number
sys.stdout.write("123\n")
sys.stdout.flush()
# You can do this split in time, like this:
sys.stdout.write("45")
sys.stdout.flush()
time.sleep(1)
sys.stdout.write("6\n")
sys.stdout.flush()
# And a new line:
sys.stdout.write("If this shows up, I work!")
sys.stdout.flush()
```
and typing into the terminal:
```
python test.py | nc localhost 8888
```
