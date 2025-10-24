#include <iostream>
using namespace std;

// 链表结点定义
struct ListNode {
    int data;
    ListNode* next;
    ListNode(int x) : data(x), next(nullptr) {}
};

/*
快慢指针在链表中的常见用法总结：

1. 检测环（Floyd判环算法）
2. 寻找链表中点
3. 查找倒数第k个结点
4. 判断链表是否为回文
5. 寻找环的起始点
6. 删除倒数第n个结点
7. 链表排序中的分割
*/

// ================ 用法一：检测环 ================
bool hasCycle(ListNode* head) {
    /*
    原理：快指针每次走2步，慢指针每次走1步
    如果有环，快指针最终会追上慢指针
    如果无环，快指针会先到达NULL
    */
    if (!head || !head->next) return false;
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast && fast->next) {
        slow = slow->next;          // 慢指针走1步
        fast = fast->next->next;    // 快指针走2步
        
        if (slow == fast) {         // 相遇说明有环
            return true;
        }
    }
    
    return false;
}

// ================ 用法二：寻找链表中点 ================
ListNode* findMiddle(ListNode* head) {
    /*
    原理：当快指针到达末尾时，慢指针恰好在中点
    奇数长度：慢指针指向正中间
    偶数长度：慢指针指向中间偏左的位置
    */
    if (!head) return nullptr;
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;  // 返回中点
}

// 变体：寻找中点偏右的位置（偶数长度时）
ListNode* findMiddleRight(ListNode* head) {
    if (!head) return nullptr;
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}

// ================ 用法三：查找倒数第k个结点 ================
ListNode* findKthFromEnd(ListNode* head, int k) {
    /*
    原理：快指针先走k步，然后快慢指针同时移动
    当快指针到达末尾时，慢指针指向倒数第k个结点
    */
    if (!head || k <= 0) return nullptr;
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    // 快指针先走k步
    for (int i = 0; i < k; i++) {
        if (!fast) return nullptr;  // k超出链表长度
        fast = fast->next;
    }
    
    // 同时移动直到快指针到达末尾
    while (fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    return slow;
}

// ================ 用法四：判断链表是否为回文 ================
bool isPalindrome(ListNode* head) {
    /*
    步骤：
    1. 用快慢指针找到中点
    2. 反转后半部分链表
    3. 比较前后两部分
    */
    if (!head || !head->next) return true;
    
    // 找到中点
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // 反转后半部分
    ListNode* secondHalf = reverseList(slow->next);
    
    // 比较前后两部分
    ListNode* p1 = head;
    ListNode* p2 = secondHalf;
    
    while (p2) {  // 后半部分可能更短
        if (p1->data != p2->data) {
            return false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    
    return true;
}

// 辅助函数：反转链表
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    
    while (curr) {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    
    return prev;
}

// ================ 用法五：寻找环的起始点 ================
ListNode* detectCycleStart(ListNode* head) {
    /*
    算法步骤：
    1. 用快慢指针检测是否有环
    2. 如果有环，将一个指针重置到头部
    3. 两个指针以相同速度移动，相遇点即为环起始点
    
    数学原理：设链表头到环起始点距离为a，环起始点到相遇点距离为b，
    相遇点到环起始点距离为c，则有：2(a+b) = a+b+c+b => a = c
    */
    if (!head || !head->next) return nullptr;
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    // 第一阶段：检测是否有环
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {  // 发现环
            break;
        }
    }
    
    if (!fast || !fast->next) {
        return nullptr;  // 无环
    }
    
    // 第二阶段：寻找环起始点
    ListNode* ptr1 = head;     // 从头开始
    ListNode* ptr2 = slow;     // 从相遇点开始
    
    while (ptr1 != ptr2) {
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    
    return ptr1;  // 环的起始点
}

// ================ 用法六：删除倒数第n个结点 ================
ListNode* removeNthFromEnd(ListNode* head, int n) {
    /*
    技巧：使用哑结点简化边界处理
    */
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    
    ListNode* slow = dummy;
    ListNode* fast = dummy;
    
    // 快指针先走n+1步
    for (int i = 0; i <= n; i++) {
        fast = fast->next;
    }
    
    // 同时移动，直到快指针到达末尾
    while (fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    // 删除结点
    ListNode* nodeToDelete = slow->next;
    slow->next = slow->next->next;
    delete nodeToDelete;
    
    return dummy->next;
}

// ================ 用法七：归并排序中的链表分割 ================
ListNode* sortList(ListNode* head) {
    /*
    归并排序步骤：
    1. 分割：用快慢指针找中点
    2. 递归排序左右两部分
    3. 合并两个有序链表
    */
    if (!head || !head->next) return head;
    
    // 找到中点并分割
    ListNode* mid = findMiddleAndSplit(head);
    
    // 递归排序
    ListNode* left = sortList(head);
    ListNode* right = sortList(mid);
    
    // 合并
    return merge(left, right);
}

ListNode* findMiddleAndSplit(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    ListNode* prev = nullptr;
    
    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    
    if (prev) prev->next = nullptr;  // 断开链表
    return slow;
}

ListNode* merge(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    
    while (l1 && l2) {
        if (l1->data <= l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

// ================ 辅助函数：创建和打印链表 ================
ListNode* createList(int arr[], int n) {
    if (n <= 0) return nullptr;
    
    ListNode* head = new ListNode(arr[0]);
    ListNode* curr = head;
    
    for (int i = 1; i < n; i++) {
        curr->next = new ListNode(arr[i]);
        curr = curr->next;
    }
    
    return head;
}

void printList(ListNode* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// ================ 测试函数 ================
void testFastSlowPointer() {
    cout << "=== 快慢指针算法测试 ===" << endl;
    
    // 创建测试链表：1->2->3->4->5
    int arr[] = {1, 2, 3, 4, 5};
    ListNode* head = createList(arr, 5);
    
    cout << "原链表: ";
    printList(head);
    
    // 测试找中点
    ListNode* mid = findMiddle(head);
    cout << "中点值: " << mid->data << endl;
    
    // 测试找倒数第2个
    ListNode* kth = findKthFromEnd(head, 2);
    cout << "倒数第2个: " << (kth ? to_string(kth->data) : "不存在") << endl;
    
    // 测试回文检测
    int palindrome[] = {1, 2, 3, 2, 1};
    ListNode* palindromeList = createList(palindrome, 5);
    cout << "回文检测: " << (isPalindrome(palindromeList) ? "是" : "否") << endl;
}

int main() {
    testFastSlowPointer();
    return 0;
}