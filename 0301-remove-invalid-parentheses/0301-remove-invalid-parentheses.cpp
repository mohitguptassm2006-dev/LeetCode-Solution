class Solution {
public:

    bool isValid(string s) {
        int count = 0;

        for(char ch : s) {
            if(ch == '(') {
                count++;
            }
            else if(ch == ')') {
                count--;

                if(count < 0) {
                    return false;
                }
            }
        }

        return count == 0;
    }

    vector<string> removeInvalidParentheses(string s) {

        vector<string> ans;
        unordered_set<string> visited;
        queue<string> q;

        q.push(s);
        visited.insert(s);

        bool found = false;

        while(!q.empty()) {

            string curr = q.front();
            q.pop();

            // Current string valid hai
            if(isValid(curr)) {
                ans.push_back(curr);
                found = true;
            }

            // Agar valid level mil gaya,
            // to next level generate nahi karna
            if(found) {
                continue;
            }

            // Ek-ek parenthesis remove karke next level banao
            for(int i = 0; i < curr.length(); i++) {

                // Letters ko remove nahi karna
                if(curr[i] != '(' && curr[i] != ')') {
                    continue;
                }

                string next = curr.substr(0, i) + curr.substr(i + 1);

                if(visited.find(next) == visited.end()) {
                    visited.insert(next);
                    q.push(next);
                }
            }
        }

        return ans;
    }
};