#include<bits/stdc++.h>
using namespace std;

/*
Assumptions
1) Employee added manually in code can be dynamic
2) Validation can put here in input fields, as of now no validation is there
3) Variants factor are ignored in course addition and slots


*/
using namespace std;

class Employee {
  public: Employee(int id,
    const string & name,
      const string & email): id(id),
  name(name),
  email(email) {}

  int getId() const {
    return id;
  }
  const string & getName() const {
    return name;
  }
  const string & getEmail() const {
    return email;
  }

  private: int id;
  string name;
  string email;
};

class CourseOffering {
  public: CourseOffering(int id,
    const string & title,
      const string & instructor,
        const string & date, int minCapacity, int maxCapacity): id(id),
  title(title),
  instructor(instructor),
  date(date),
  minCapacity(minCapacity),
  maxCapacity(maxCapacity),
  isCancelled(false) {}

  int getId() const {
    return id;
  }
  const string & getTitle() const {
    return title;
  }
  const string & getInstructor() const {
    return instructor;
  }
  const string & getDate() const {
    return date;
  }
  int getMinCapacity() const {
    return minCapacity;
  }
  int getMaxCapacity() const {
    return maxCapacity;
  }
  bool isCancelledOffering() const {
    return isCancelled;
  }

  void addEmployee(int employeeId) {
    if (registrations.size() <= maxCapacity) {
      registrations.push_back(employeeId);
      if (registrations.size() >= minCapacity) {
        isCancelled = false; // Minimum registrations met, course is confirmed
      }
    }
  }

  void cancelEmployee(int employeeId) {
    registrations.erase(remove(registrations.begin(), registrations.end(), employeeId), registrations.end());
    if (registrations.size() < minCapacity) {
      isCancelled = true; // Minimum registrations not met, course is cancelled
    }
  }

  const vector < int > getRegistrations() const {
    return registrations;
  }

  private: int id;
  string title;
  string instructor;
  string date;
  int minCapacity;
  int maxCapacity;
  bool isCancelled;
  vector < int > registrations;
};

vector < Employee > employees;
vector < CourseOffering > courseOfferings;

void performCourseAllotment() {
    for (CourseOffering & offering : courseOfferings) {
        if (offering.isCancelledOffering()) {
            cout << "Course '" << offering.getTitle() << "' (ID: " << offering.getId() << ") has been canceled due to insufficient registrations." << endl;
        } else {
            cout << "Course Allotment for '" << offering.getTitle() << "' (ID: " << offering.getId() << "):" << endl;
            for (int employeeId : offering.getRegistrations()) {
                const Employee & employee = employees[employeeId];
                cout << "Registration Number: " << employee.getId() << " | Employee Name: " << employee.getName()
                     << " | Email: " << employee.getEmail() << " | Course Offering ID: " << offering.getId()
                     << " | Course Name: " << offering.getTitle() << " | Instructor: " << offering.getInstructor()
                     << " | Date: " << offering.getDate() << " | Final Status: Accepted" << endl;
            }
        }
    }
}
void showEmployee(vector < Employee > v) {
  for (auto m: v) {
    cout << m.getId() << " " << m.getName() << " " << m.getEmail() << endl;
  }
  cout << endl;
}

int main() {

  employees.push_back({
    1,
    "Alice",
    "alice@example.com"
  });
  employees.push_back({
    2,
    "Bob",
    "bob@example.com"
  });
  employees.push_back({
    3,
    "Charlie",
    "charlie@example.com"
  });
  while (true) {
    cout << "1. Add Course Offering" << endl;
    cout << "2. Register for Course" << endl;
    cout << "3. Cancel Registration" << endl;
    cout << "4. Perform Course Allotment" << endl;
    cout << "5. Show Employees" << endl;
    cout << "6. Exit" << endl;

    int choice;
    cin >> choice;

    if (choice == 1) {
      int courseId, minCapacity, maxCapacity;
      string title, instructor, date;
      cout << "Enter Course ID: ";
      cin >> courseId;
      cout << "Enter Course Title: ";
      cin >> title;
      cout << "Enter Instructor: ";
      cin >> instructor;
      cout << "Enter Date: ";
      cin >> date;
      cout << "Enter Minimum Capacity: ";
      cin >> minCapacity;
      cout << "Enter Maximum Capacity: ";
      cin >> maxCapacity;

      CourseOffering course(courseId, title, instructor, date, minCapacity, maxCapacity);
      courseOfferings.push_back(course);
      cout << "Course Offering Added." << endl;
    } else if (choice == 2) {
      int courseId, employeeId;
      cout << "Enter Course ID: ";
      cin >> courseId;
      cout << "Enter Employee ID: ";
      cin >> employeeId;

      if (courseId >= 0 && courseId <= courseOfferings.size() && employeeId >= 0 && employeeId <= employees.size()) {
        courseOfferings[courseId].addEmployee(employeeId);
        cout << "Registration Accepted." << endl;
      } else {
        cout << "Invalid Course or Employee ID." << endl;
      }
    } else if (choice == 3) {
      int courseId, employeeId;
      cout << "Enter Course ID: ";
      cin >> courseId;
      cout << "Enter Employee ID: ";
      cin >> employeeId;

      if (courseId >= 0 && courseId <= courseOfferings.size() && employeeId >= 0 && employeeId <= employees.size()) {
        courseOfferings[courseId].cancelEmployee(employeeId);
        cout << "Registration Cancelled." << endl;
      } else {
        cout << "Invalid Course or Employee ID." << endl;
      }
    } else if (choice == 4) {
      performCourseAllotment();
      for (CourseOffering & offering: courseOfferings) {
        if (offering.isCancelledOffering()) {
          cout << "Course '" << offering.getTitle() << "' (ID: " << offering.getId() << ") has been canceled due to insufficient registrations." << endl;
        }
      }
    } else if (choice == 5) {
      showEmployee(employees);
    } else if (choice == 6) {
      break;
    }

  }

  return 0;
}
