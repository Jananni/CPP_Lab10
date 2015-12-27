
// Used sample solution from assignment 10

#include <string>
#include <iostream>
#include <sstream>
using namespace std;

// class Student prototype -----------------------
class Student
{
private:
   string lastName;
   string firstName;
   int totalPoints;

public:
   static const string DEFAULT_NAME;
   static const int DEFAULT_POINTS = 0;
   static const int MAX_POINTS = 1000;

public:
   Student(string lst = DEFAULT_NAME, string fst = DEFAULT_NAME,
           long pts = DEFAULT_POINTS);

   // accessors and mutators
   string getLastName() { return lastName; }
   string getFirstName() { return firstName; }
   int getTotalPoints() { return totalPoints; }

   bool setLastName(string last);
   bool setFirstName(string first);
   bool setPoints(int pts);

   static int compareTwoStudents( Student firstStud, Student secondStud );
   string toString();

private:
   static bool validString( string testStr );
   static bool validPoints( int testPoints );

   // sort and ordering support
public:
   static  const int SORT_BY_FIRST = 88;
   static  const int SORT_BY_LAST = 98;
   static  const int SORT_BY_POINTS = 108;

private:
   static int sortKey;

public:
   static bool setSortKey( int key );
   static  int getSortKey() { return sortKey; }
};  // end of class Student prototype --------------

int Student::sortKey = Student::SORT_BY_LAST;

// class StudentArrayUtilities prototype -----------------------
class StudentArrayUtilities
{
public:
   bool addStudent(Student stud);
   Student removeStudent();
   string toString(string title);
   void arraySort();
   double getMedianDestructive();
   static const int MAX_STUDENTS = 20;

private:
   static void mySwap(Student &a, Student &b);
   bool floatLargestToTop(int top);
   int numStudents;
   Student theArray[MAX_STUDENTS];

public:
   StudentArrayUtilities() { numStudents = 0; };
};

// static initializations that can't be done in-line
const string Student::DEFAULT_NAME = "zz-error";

int main()
{
   int k;
   Student  myClass[] =
   {
      Student("smith","fred", 95),
      Student("bauer","jack",123),
      Student("jacobs","carrie", 195),
      Student("renquist","abe",148),
      Student("jackson","trevor", 108),
      Student("perry","fred",225),
      Student("loceff","fred", 44),
      Student("stollings","pamela",452),
      Student("charters","rodney", 295),
      Student("cassar","john",321)
   };

   Student student;
   int arraySize = sizeof(myClass) / sizeof(myClass[0]);

   // instantiate an SAU object
   StudentArrayUtilities myStuds;

   // we can add stdunts manually and individually
   myStuds.addStudent( Student( "bartman", "petra", 102 ) );
   myStuds.addStudent( Student( "charters", "rodney", 295 ) );
   myStuds.addStudent( Student( "a", "m", 1 ) );
   myStuds.addStudent( Student( "b", "n", 2 ) );
   myStuds.addStudent( Student( "c", "o", 3 ) );
   myStuds.addStudent( Student( "d", "p", 4 ) );
   myStuds.addStudent( Student( "e", "q", 5 ) );
   myStuds.addStudent( Student( "f", "r", 6 ) );
   myStuds.addStudent( Student( "g", "s", 7 ) );
   myStuds.addStudent( Student( "h", "t", 8 ) );
   myStuds.addStudent( Student( "i", "u", 9 ) );

   // if we happen to have an array available, we can add students in loop.
   for ( k = 0; k < arraySize; k++ )
      myStuds.addStudent( myClass[k] );

   cout << myStuds.toString( "Before: " );

   myStuds.arraySort();
   cout << myStuds.toString("After default sort: ");

   Student::setSortKey(Student::SORT_BY_FIRST);
   myStuds.arraySort();
   cout << myStuds.toString( "After sort by first: " );

   // test median
   cout << "Median of evenClass = "
   << myStuds.getMedianDestructive()
   << endl << endl;

   // various tests of removing and adding too many students
   for (k = 0; k < 100; k++)
   {
      student = myStuds.removeStudent();
      if ( Student::compareTwoStudents( student, Student() ) )
         cout << "Removed " << student.toString();
      else
      {
         cout << endl << "Empty after " << k << " removes." << endl;
         break;
      }
   }

   for (k = 0; k < 100; k++)
   {
      if (!myStuds.addStudent(Student("first", "last", 22)))
      {
         cout << "Full after " << k << " adds." << endl << endl;
         break;
      }
   }
}

// beginning of Student method definitions -------------
Student::Student( string last, string first, long points)
{
   if ( !setLastName(last) )
      lastName = DEFAULT_NAME;
   if ( !setFirstName(first) )
      firstName = DEFAULT_NAME;
   if ( !setPoints(points) )
      totalPoints = DEFAULT_POINTS;
}

bool Student::setLastName(string last)
{
   if ( !validString(last) )
      return false;
   lastName = last;
   return true;
}

bool Student::setFirstName(string first)
{
   if ( !validString(first) )
      return false;
   firstName = first;
   return true;
}

bool Student::setPoints(int pts)
{
   if ( !validPoints(pts) )
      return false;
   totalPoints = pts;
   return true;
}

string Student::toString()
{
   string resultString;
   ostringstream cnvrtFirst, cnvrtLast, cnvrtPoints;

   cnvrtFirst << firstName;
   cnvrtLast << lastName;
   cnvrtPoints << totalPoints;

   resultString = " "+ cnvrtLast.str()
   + ", " + cnvrtFirst.str()
   + " points: " + cnvrtPoints.str()
   + "\n";
   return resultString;
}

bool Student::validString( string testStr )
{
   if (testStr.length() > 0 && isalpha(testStr[0]))
      return true;
   return false;
}

bool Student::validPoints( int testPoints )
{
   if (testPoints >= 0 && testPoints <= MAX_POINTS)
      return true;
   return false;
}

bool Student::setSortKey( int key )
{
   switch ( key )
   {
      case SORT_BY_FIRST:
      case SORT_BY_LAST:
      case SORT_BY_POINTS:
         sortKey = key;
         return true;
      default:
         return false;
   }
}

int Student::compareTwoStudents( Student firstStud, Student secondStud )
{
   switch ( sortKey )
   {
      case SORT_BY_FIRST:
         return   firstStud.firstName.compare( secondStud.firstName );
      case SORT_BY_LAST:
         return   firstStud.lastName.compare( secondStud.lastName );
      case SORT_BY_POINTS:
         return firstStud.totalPoints - secondStud.totalPoints;
      default:
         // should never happen - this default case can be omitted, safely
         return 0;
   }
}

// end of Student method definitions  --------------

// beginning of StudentArrayUtilities method definitions -------------
string StudentArrayUtilities::toString(string title)
{
   string output = "";

   output =  title + "\n";

   // build the output string from the individual Students:
   for (int k = 0; k < numStudents; k++)
      output += " "+ theArray[k].toString();

   return (output + "\n");
}

void StudentArrayUtilities::arraySort()
{
   for (int k = 0; k < numStudents; k++)
      // compare with method def to see where inner loop stops
      if (!floatLargestToTop(numStudents - 1 - k))
         return;
}

// returns true if a modification was made to the array
bool StudentArrayUtilities::floatLargestToTop(int top)
{
   bool changed = false;

   // compare with client call to see where the loop stops
   for (int k = 0; k < top; k++)
      if (  Student::compareTwoStudents(theArray[k], theArray[k+1]) > 0 )
      {
         mySwap(theArray[k], theArray[k+1]);
         changed = true;
      }
   return changed;
}

void StudentArrayUtilities::mySwap(Student &a, Student &b)
{
   Student temp("", "", 0);

   temp = a;
   a = b;
   b = temp;
}

// median -- this method is allowed to return with array in new order
double StudentArrayUtilities::getMedianDestructive()
{
   int saveSortKey, justBelow, justAbove;
   double retVal;

   retVal = 0.;

   if ( numStudents <= 0 )
      return 0;
   if ( numStudents == 1 )
      return theArray[0].getTotalPoints();

   // preserve the client's sortKey
   saveSortKey = Student::getSortKey();

   // sort by points to prep for computing median
   Student::setSortKey( Student::SORT_BY_POINTS );
   arraySort();

   if ( numStudents % 2 == 0 )
   {
      justBelow = (numStudents / 2 - 1);
      justAbove = numStudents / 2;
      retVal = (theArray[justBelow].getTotalPoints()
                + theArray[justAbove].getTotalPoints()) / 2.0;  //need double
   }
   else
      retVal = theArray[numStudents / 2].getTotalPoints();

   // restore the sort key to what it was before the call
   Student::setSortKey( saveSortKey );
   return retVal;
}

bool StudentArrayUtilities::addStudent(Student stud)
{
   if ( numStudents >= MAX_STUDENTS )
   {
      return false;
   }
   theArray[numStudents++] = stud;
   return true;
}

Student StudentArrayUtilities::removeStudent()
{
   if ( numStudents <= 0 )
   {
      return Student();
   }
   return theArray[--numStudents];
}
// end of StudentArrayUtilities method definitions  -----------

/* -------------------------- run ------------------------------------------
 
 Before:
 bartman, petra points: 102
 charters, rodney points: 295
 a, m points: 1
 b, n points: 2
 c, o points: 3
 d, p points: 4
 e, q points: 5
 f, r points: 6
 g, s points: 7
 h, t points: 8
 i, u points: 9
 smith, fred points: 95
 bauer, jack points: 123
 jacobs, carrie points: 195
 renquist, abe points: 148
 jackson, trevor points: 108
 perry, fred points: 225
 loceff, fred points: 44
 stollings, pamela points: 452
 charters, rodney points: 295

 After default sort:
 a, m points: 1
 b, n points: 2
 bartman, petra points: 102
 bauer, jack points: 123
 c, o points: 3
 charters, rodney points: 295
 charters, rodney points: 295
 d, p points: 4
 e, q points: 5
 f, r points: 6
 g, s points: 7
 h, t points: 8
 i, u points: 9
 jackson, trevor points: 108
 jacobs, carrie points: 195
 loceff, fred points: 44
 perry, fred points: 225
 renquist, abe points: 148
 smith, fred points: 95
 stollings, pamela points: 452

 After sort by first:
 renquist, abe points: 148
 jacobs, carrie points: 195
 loceff, fred points: 44
 perry, fred points: 225
 smith, fred points: 95
 bauer, jack points: 123
 a, m points: 1
 b, n points: 2
 c, o points: 3
 d, p points: 4
 stollings, pamela points: 452
 bartman, petra points: 102
 e, q points: 5
 f, r points: 6
 charters, rodney points: 295
 charters, rodney points: 295
 g, s points: 7
 h, t points: 8
 jackson, trevor points: 108
 i, u points: 9

 Median of evenClass = 69.5

 Removed  stollings, pamela points: 452
 Removed  charters, rodney points: 295
 Removed  charters, rodney points: 295
 Removed  perry, fred points: 225
 Removed  jacobs, carrie points: 195
 Removed  renquist, abe points: 148
 Removed  bauer, jack points: 123
 Removed  jackson, trevor points: 108
 Removed  bartman, petra points: 102
 Removed  smith, fred points: 95
 Removed  loceff, fred points: 44
 Removed  i, u points: 9
 Removed  h, t points: 8
 Removed  g, s points: 7
 Removed  f, r points: 6
 Removed  e, q points: 5
 Removed  d, p points: 4
 Removed  c, o points: 3
 Removed  b, n points: 2
 Removed  a, m points: 1

 Empty after 20 removes.
 Full after 20 adds.

 Program ended with exit code: 0

 ------------------------------------------------------------------------- */
