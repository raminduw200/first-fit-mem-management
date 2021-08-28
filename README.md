# First fit memory management and sleeping barber problem (without synchronization )
###Question 1
Memory Management is the act of managing computer memory at the system level.
The essential requirement of memory management is to provide ways to dynamically
allocate  portions of memory to programs (user processes) at their request, and free it
for  reuse  when  no  longer  needed.  Consider  the  following  scenario  in  relation  to  the
“First Fit Algorithm” in memory management.

Each  user  process  (job)  requests  a  particular  size  of  memory  that  must  be  made
available contiguously (one block). If such a memory partition exists, it is allocated to
the  requested  process.  If  that  memory  partition  is  too  large  to  accommodate  the
process, the memory block is divided into two parts. One to accommodate the process
and other one is kept as a free space block. When a job terminates, its allocated block
of memory becomes a free space. If one assumes the memory size is 2560k and 400k is
allocated  for  operating  system  files,  the  remaining  memory  is  reserved  for  user
processes. An illustrative example of the memory management is given below.

![expected_output_screenshot](question/output.png?raw=true "Output")

Use  C  programming  language  to  implement  a  Memory  Management  scenario  using
pointers and appropriate data structure. You should design a suitable interface to input
the ProcessID along with the memory size it requires.

Your  code  should  include  the  relevant  class  definitions  and  method  definitions  (for
allocating and releasing memory). A method to print a current snapshot of the memory
is also required.

###Question 2
Write a C program which implements a solution to the sleeping barber problem
Details of the sleeping barber synchronization problem:
A barbershop  consists  of  a waiting room with  n-1 chairs,  and a  barber  room
with one chair (for a total of n chairs).
- There are x clients and one barber in the system.
- The following rules apply:
    - If there are no clients in his shop, the barber goes to sleep.
    - If a client comes in, and the barber is asleep, the client wakes the
barber and gets a haircut.
    - If the barber is busy, and there is a chair available, the client sits and
waits.
    - If there are no chairs available when a client arrives, he leaves.
    
##Program Output
### First fit memory management
![first_fit_screenshot](question/first_fit.png?raw=true "Output")

### Sleeping barber
- Barber take random time to cut a customer's hair
![sleeping_barber_screenshot](question/sleeping_barber.png?raw=true "Output")
