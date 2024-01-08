#include<bits/stdc++.h>
using namespace std;

class Member{
public:
    string name;
    string bloodGroup;
    int age;
    Member(const string &_name, const string &_bloodGroup, int _age)
        : name(_name), bloodGroup(_bloodGroup), age(_age) {}
};

class Node{
public:
    Member member;
    Node *next;
    Node *prev;
    Node(const Member &_member) : member(_member), next(nullptr), prev(nullptr) {}
};

class BloodGroupManagement{
private:
    Node *head = nullptr;
    Node *tail = nullptr;

    Node *createNode(const Member &member){
        return new Node(member);
    }

    void quickSort(vector<Member> &arr, int low, int high){
        if (low < high){
            int pivot = partition(arr, low, high);
            quickSort(arr, low, pivot - 1);
            quickSort(arr, pivot + 1, high);
        }
    }

    int partition(vector<Member> &arr, int low, int high){
        string pivot = arr[high].bloodGroup;
        int i = low - 1;
        for (int j = low; j <= high - 1; j++){
            if (arr[j].bloodGroup <= pivot){
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    int binarySearch(const vector<Member> &arr, const string &bloodGroup){
        int left = 0;
        int right = arr.size() - 1;
        while (left <= right){
            int mid = left + (right - left) / 2;
            if (arr[mid].bloodGroup == bloodGroup) return mid;
            else if (arr[mid].bloodGroup < bloodGroup) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }

public:
    void addMember(const Member &member){
        Node *newNode = createNode(member);
        if (head == nullptr){
            head = newNode;
            tail = newNode;
        }else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void searchMembers(const string &bloodGroup){
        if (head == nullptr){
            cout << "The list is empty." << endl;
            return;
        }
        vector<Member> members;
        Node *curr = head;
        while (curr != nullptr){
            members.push_back(curr->member);
            curr = curr->next;
        }

        quickSort(members, 0, members.size() - 1);
        
        bool found = false;
        cout << "Members with Blood Group '" << bloodGroup << "':" << endl;
        for (const auto &member : members){
            if (member.bloodGroup == bloodGroup){
                cout << "Name: " << member.name << "\tBlood Group: " << member.bloodGroup << "\tAge: " << member.age << endl;
                found = true;
            }
        }
        if (!found){
            cout << "No members found with Blood Group '" << bloodGroup << "'." << endl;
        }
    }

    void deleteMember(const string &name){
        if (head == nullptr){
            cout << "The list is empty." << endl;
            return;
        }
        Node *curr = head;
        while (curr != nullptr && curr->member.name != name)
            curr = curr->next;

        if (curr == nullptr){
            cout << "Member '" << name << "' not found." << endl;
            return;
        }
        if (curr == head){
            head = head->next;
            if (head != nullptr) head->prev = nullptr;
            else tail = nullptr;
        }else if (curr == tail){
            tail = tail->prev;
            tail->next = nullptr;
        }else {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }
        delete curr;
        cout << "Member '" << name << "' deleted successfully." << endl;
    }
    void viewMembers(){
        if (head == nullptr){
            cout << "The list is empty." << endl;
            return;
        }
        Node *curr = head;
        cout << endl << "All Members: " << endl << "---------------------------------------" << endl;
        while (curr != nullptr){
            cout << "Name: " << curr->member.name << "\tBlood Group: " << curr->member.bloodGroup << "\t Age: " << curr->member.age << endl;
            curr = curr->next;
        }
        cout << "---------------------------------------" << endl;
    }
    void saveData(){
        ofstream file("members.txt");
        if (!file.is_open()){
            cout << "Error opening file." << endl;
            return;
        }
        Node *curr = head;
        while (curr != nullptr){
            file << curr->member.name << ";" << curr->member.bloodGroup << ";" << curr->member.age << endl;
            curr = curr->next;
        }
        file.close();
        cout << "Data saved successfully." << endl;
    }
    void loadData(){
        ifstream file("members.txt");
        if (!file.is_open()){
            cout << "No data file found." << endl;
            return;
        }
        string line;
        while (getline(file, line)){
            size_t pos1 = line.find(";");
            size_t pos2 = line.find(";", pos1 + 1);
            string name = line.substr(0, pos1);
            string bloodGroup = line.substr(pos1 + 1, pos2 - pos1 - 1);
            int age = stoi(line.substr(pos2 + 1));

            Member member(name, bloodGroup, age);
            addMember(member);
        }
        file.close();
        cout << "Data loaded successfully." << endl;
    }
};

int main(){
    BloodGroupManagement bloodGroupManager;
    int choice;
    string name, bloodGroup;

    bloodGroupManager.loadData();

    while (true){
        cout << "\nBlood Group Management System" << endl;
        cout << "1. Add Member" << endl;
        cout << "2. Delete Member" << endl;
        cout << "3. View Members" << endl;
        cout << "4. Search Blood" << endl;
        cout << "5. Save Data" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice){
        case 1:
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Blood Group: ";
            cin >> bloodGroup;
            int age;
            cout << "Enter Age: ";
            cin >> age;
            bloodGroupManager.addMember(Member(name, bloodGroup, age));
            break;
        case 2:
            cout << "Enter Name to delete: ";
            cin >> name;
            bloodGroupManager.deleteMember(name);
            break;
        case 3:
            bloodGroupManager.viewMembers();
            break;
        case 4:
            cout << "Enter Blood Group to search: ";
            cin >> bloodGroup;
            cout << "---------------------------------------" << endl;
            bloodGroupManager.searchMembers(bloodGroup);
            cout << "---------------------------------------" << endl;
            break;
        case 5:
            bloodGroupManager.saveData();
            break;
        case 6:
            cout << "Exiting..." << endl;
            bloodGroupManager.saveData();
            exit(0);
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}