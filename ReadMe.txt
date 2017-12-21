Formatting:

Reader Data file:
First int in file states number of readers,
0 TA224Student 224 0 0 0 
0/1 depicts if teacher(1) or student(0)
Username
Password
# of copies currently keeping
# of books reserved
# of books allowed (dependent on penalties)

Book Data File:
First int in file states number of books,
978-1-60309-056-8		//ISBN of book
The Amazing Programmer 	//Title of book
Kyle Kelly				//Author of Book
Comedy					//Category of Book
1						//Number of Students Reserving
bryceStudent			//Student Reserving

Copy Data File:
First int states number of copies 
972-4-88301-046-6 5436783 noborrower 0 0 0
ISBN of book
Copy ID #
name of borrower (noborrower = null)
borrow Date
Reserve Date
Expiration Date

Librarian Data File:
3 0 1
Number of librarians, date they enter, date the leave
TA224 224
username password

