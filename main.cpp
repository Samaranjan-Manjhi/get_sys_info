#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <unistd.h>  
using namespace std;

// Function to execute a shell command and return its output as a string
string executeCommand(const string& command) {
     shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
     if (!pipe) {
          throw runtime_error("popen() failed!");
     }
     char buffer[128];
     string result = "";
     while (!feof(pipe.get())) {
          if (fgets(buffer, 128, pipe.get()) != nullptr) {
               result += buffer;
          }
     }
     return result;
}

// Function to display log files
void displayLog(const string& logFileName) {
     ifstream logFile(logFileName);
     if (logFile.is_open()) {
          string line;
          while (getline(logFile, line)) {
               cout << line << endl;
          }
          logFile.close();
     } else {
          cerr << "Failed to open " << logFileName << endl;
     }
}

// Function to display file contents
void displayFileContents(const string& fileName) {
     ifstream file(fileName);
     if (file.is_open()) {
          string line;
          while (getline(file, line)) {
               cout << line << endl;
          }
          file.close();
     } else {
          cerr << "Failed to open " << fileName << endl;
     }
}

int main() {
     int choice;
     int processChoice;
     string processName;
     int logsChoice;
     int modulesChoice;
     int userGroupChoice;
     int runlevelChoice;
     int result; 
     string pgrepCommand; 
     string moduleName;
     string modinfoCommand;

     while (true) {
          cout << endl;
          cout << "Linux System Information:" << endl;
          cout << "1. Hostname and System Identification" << endl;
          cout << "2. Kernel and System Information" << endl;
          cout << "3. Distribution-Specific Information" << endl;
          cout << "4. CPU Information" << endl;
          cout << "5. Memory Information" << endl;
          cout << "6. Disk and File System Information" << endl;
          cout << "7. Network Information" << endl;
          cout << "8. Hardware Information" << endl;
          cout << "9. Software Information" << endl;
          cout << "10. Processes Information" << endl;
          cout << "11. System Logs and Authentication Logs" << endl;
          cout << "12. Users and Groups Information" << endl;
          cout << "13. Runlevel and Services Information" << endl;
          cout << "14. Kernel Modules Information" << endl;
          cout << "15. Exit" << endl;
          cout << "Enter your choice: ";
          cin >> choice;

          switch (choice) {
               case 1:
                    cout << "\t\t\t------------------Output----------------\n" << endl;
                    cout << "Hostname and System Identification:" << endl;
                    system("hostnamectl");
                    cout << endl;
                    break;
               case 2:
                    cout << "\t\t\t------------------Output----------------\n" << endl;
                    cout << "Kernel and System Information:" << endl;
                    system("uname -a");
                    cout << endl;
                    break;
               case 3:
                    cout << "\t\t\t------------------Output----------------\n" << endl;
                    cout << "Distribution-Specific Information:" << endl;
                    system("lsb_release -a");
                    cout << endl;
                    break;
               case 4:
                    cout << "\t\t\t------------------Output----------------\n" << endl;
                    cout << "CPU Information:" << endl;
                    system("lscpu");
                    system("cat /proc/cpuinfo");
                    cout << endl;
                    break;
               case 5:
                    cout << "\t\t\t------------------Output----------------\n" << endl;
                    cout << "Memory Information:" << endl;
                    system("free -m");
                    system("cat /proc/meminfo");
                    cout << endl;
                    break;
               case 6:
                    cout << "\t\t\t------------------Output----------------\n" << endl;
                    cout << "Disk and File System Information:" << endl;
                    system("df -h");
                    system("lsblk");
                    system("fdisk -l");
                    system("mount");
                    cout << endl;
                    break;
               case 7:
                    cout << "\t\t\t------------------Output----------------\n" << endl;
                    cout << "Network Information:" << endl;
                    system("ifconfig");
                    system("netstat -tuln");
                    system("route -n");
                    cout << endl;
                    break;
               case 8:
                    cout << "\t\t\t------------------Output----------------\n" << endl;
                    cout << "Hardware Information:" << endl;
                    system("lshw");
                    system("lspci");
                    system("lsusb");
                    cout << endl;
                    break;
               case 9:
                    cout << "\t\t\t------------------Output----------------\n" << endl;
                    cout << "Software Information:" << endl;
                    system("dpkg -l");
                    system("rpm -qa");
                    system("dpkg -l | grep ^ii");
                    system("rpm -qa | sort");
                    system("cat /etc/apt/sources.list");
                    system("cat /etc/yum.repos.d/*.repo");
                    cout << endl;
                    break;
               case 10:
                    while (true) {
                         cout << "Processes Information:" << endl;
                         cout << "1. Display real-time system statistics (top or htop)" << endl;
                         cout << "2. List all processes and their details (ps aux)" << endl;
                         cout << "3. Get the process ID (PID) of a specific process (pgrep)" << endl;
                         cout << "4. Back to Main Menu" << endl;
                         cout << "Enter your choice: ";
                         cin >> processChoice;
                         switch (processChoice) {
                              case 1:
                                   cout << "\t\t\t------------------Output----------------\n" << endl;
                                   system("top");
                                   cout << endl;
                                   break;
                              case 2:
                                   cout << "\t\t\t------------------Output----------------\n" << endl;
                                   system("ps aux");
                                   cout << endl;
                                   break;
                              case 3:
                                   cout << "Enter the process name: ";
                                   cin >> processName;
                                   pgrepCommand = "pgrep " + processName;
                                   result = system(pgrepCommand.c_str());
                                   if (WIFEXITED(result) && WEXITSTATUS(result) == 0) {
                                        cout << "\t\t\t------------------Output----------------\n" << endl;
                                        cout << "Process ID (PID): " << WEXITSTATUS(result) << endl;
                                        cout << endl;
                                   } else {
                                        cout << "\t\t\t------------------Output----------------\n" << endl;
                                        cerr << "Process not found or an error occurred." << endl;
                                        cout << endl;
                                   }
                                   break;
                              case 4:
                                   break;
                              default:
                                   cout << "Invalid choice. Please try again." << endl;
                         }
                         if (processChoice == 4) {
                              break;
                         }
                    }
                    break;
               case 11:
                    while (true) {
                         cout << "System Logs and Authentication Logs:" << endl;
                         cout << "1. Display system logs" << endl;
                         cout << "2. Display authentication logs" << endl;
                         cout << "3. Back to Main Menu" << endl;
                         cout << "Enter your choice: ";
                         cin >> logsChoice;
                         switch (logsChoice) {
                              case 1:
                                   cout << "\t\t\t------------------Output----------------\n" << endl;
                                   system("cat /var/log/syslog");
                                   cout << endl;
                                   break;
                              case 2:
                                   cout << "\t\t\t------------------Output----------------\n" << endl;
                                   if (access("/var/log/auth.log", F_OK) != -1) {
                                        system("cat /var/log/auth.log");
                                        cout << endl;
                                   } else if (access("/var/log/secure", F_OK) != -1) {
                                        cout << "\t\t\t------------------Output----------------\n" << endl;
                                        system("cat /var/log/secure");
                                        cout << endl;
                                   } else {
                                        cout << "\t\t\t------------------Output----------------\n" << endl;
                                        cerr << "Authentication log file not found." << endl;
                                        cout << endl;
                                   }
                                   break;
                              case 3:
                                   break;
                              default:
                                   cout << "Invalid choice. Please try again." << endl;
                         }
                         if (logsChoice == 3) {
                              break;
                         }
                    }
                    break;
               case 12:
                    while (true) {
                         cout << "Users and Groups Information:" << endl;
                         cout << "1. List User Accounts" << endl;
                         cout << "2. List Group Accounts" << endl;
                         cout << "3. Back to Main Menu" << endl;
                         cout << "Enter your choice: ";
                         cin >> userGroupChoice;
                         switch (userGroupChoice) {
                              case 1:
                                   cout << "\t\t\t------------------Output----------------\n" << endl;
                                   system("cat /etc/passwd");
                                   cout << endl;
                                   break;
                              case 2:
                                   cout << "\t\t\t------------------Output----------------\n" << endl;
                                   system("cat /etc/group");
                                   cout << endl;
                                   break;
                              case 3:
                                   cout << "\t\t\t------------------Output----------------\n" << endl;
                                   break;
                              default:
                                   cout << "Invalid choice. Please try again." << endl;
                         }
                         if (userGroupChoice == 3) {
                              break;
                         }
                    }
                    break;
               case 13:
                    while (true) {
                         cout << "Runlevel and Services Information:" << endl;
                         cout << "1. Show Current Runlevel" << endl;
                         cout << "2. List Available Services" << endl;
                         cout << "3. Back to Main Menu" << endl;
                         cout << "Enter your choice: ";
                         cin >> runlevelChoice;
                         switch (runlevelChoice) {
                              case 1:
                                   cout << "\t\t\t------------------Output----------------\n" << endl;
                                   system("runlevel");
                                   cout << endl;
                                   break;
                              case 2:
                                   cout << "\t\t\t------------------Output----------------\n" << endl;
                                   system("service --status-all 2>&1 || systemctl list-units --type=service");
                                   cout << endl;
                                   break;
                              case 3:
                                   break;
                              default:
                                   cout << "Invalid choice. Please try again." << endl;
                         }
                         if (runlevelChoice == 3) {
                              break;
                         }
                    }
                    break;
               case 14:
                    while (true) {
                         cout << "Kernel Modules Information:" << endl;
                         cout << "1. List Loaded Kernel Modules (lsmod)" << endl;
                         cout << "2. Display Information About a Specific Kernel Module (modinfo)" << endl;
                         cout << "3. Back to Main Menu" << endl;
                         cout << "Enter your choice: ";
                         cin >> modulesChoice;
                         switch (modulesChoice) {
                              case 1:
                                   cout << "\t\t\t------------------Output----------------\n" << endl;
                                   system("lsmod");
                                   cout << endl;
                                   break;
                              case 2:
                                   cout << "\t\t\t------------------Output----------------\n" << endl;
                                   cout << "Enter the name of the kernel module: ";
                                   cin >> moduleName;
                                   modinfoCommand = "modinfo " + moduleName;
                                   system(modinfoCommand.c_str());
                                   cout << endl;
                                   break;
                              case 3:
                                   break;
                              default:
                                   cout << "Invalid choice. Please try again." << endl;
                         }
                         if (modulesChoice == 3) {
                              break;
                         }
                    }
                    break;
               case 15:
                    return 0;
               default:
                    cout << "Invalid choice. Please try again." << endl;
          }
     }

     return 0;
}

