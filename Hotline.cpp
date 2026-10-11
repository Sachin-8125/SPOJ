#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Statement {
    string subject;   // "I", "you", "everybody", "nobody", or specific name
    string verb;      // base form (infinitive)
    string object;    // text of object (can be empty)
    bool is_negative; // true if negative
    bool is_generic;  // true if "everybody" or "nobody"
};

// Check if two statements contradict each other
bool contradict(const Statement& s1, const Statement& s2) {
    if (s1.verb != s2.verb || s1.object != s2.object) return false;
    if (s1.is_negative == s2.is_negative) return false;

    // Both are generic ("everybody" vs "nobody")
    if (s1.is_generic && s2.is_generic) return true;

    // One is generic and one is specific
    if (s1.is_generic || s2.is_generic) return true;

    // Both are specific subjects
    if (s1.subject == s2.subject) return true;

    return false;
}

Statement parseStatement(const string& line) {
    Statement stmt;
    string s = line.substr(0, line.length() - 1); // remove '.'
    size_t sp1 = s.find(' ');
    string word1 = s.substr(0, sp1);
    string rest1 = s.substr(sp1 + 1);

    size_t sp2 = rest1.find(' ');
    string word2 = (sp2 == string::npos) ? rest1 : rest1.substr(0, sp2);

    if (word2 == "don't" || word2 == "doesn't") {
        stmt.subject = word1;
        stmt.is_negative = true;
        stmt.is_generic = false;
        string rest2 = rest1.substr(sp2 + 1);
        size_t sp3 = rest2.find(' ');
        if (sp3 == string::npos) {
            stmt.verb = rest2;
            stmt.object = "";
        } else {
            stmt.verb = rest2.substr(0, sp3);
            stmt.object = rest2.substr(sp3 + 1);
        }
    } else {
        stmt.subject = word1;
        string verb_token = word2;
        if (sp2 == string::npos) {
            stmt.object = "";
        } else {
            stmt.object = rest1.substr(sp2 + 1);
        }

        if (stmt.subject == "nobody") {
            stmt.is_negative = true;
            stmt.is_generic = true;
            stmt.verb = verb_token.substr(0, verb_token.length() - 1);
        } else if (stmt.subject == "everybody") {
            stmt.is_negative = false;
            stmt.is_generic = true;
            stmt.verb = verb_token.substr(0, verb_token.length() - 1);
        } else {
            stmt.is_negative = false;
            stmt.is_generic = false;
            if (stmt.subject == "I" || stmt.subject == "you") {
                stmt.verb = verb_token;
            } else {
                stmt.verb = verb_token.substr(0, verb_token.length() - 1);
            }
        }
    }
    return stmt;
}

// 1. do|does subject predicate [object] ?
string answerType1(const string& q_subject, const string& q_verb, const string& q_object, const vector<Statement>& stmts) {
    string ans_subject = (q_subject == "I") ? "you" : (q_subject == "you" ? "I" : q_subject);

    bool pos = false, neg = false;
    for (const auto& s : stmts) {
        if (s.verb == q_verb && s.object == q_object) {
            if (!s.is_negative) {
                if (s.subject == "everybody" || s.subject == q_subject) pos = true;
            } else {
                if (s.subject == "nobody" || s.subject == q_subject) neg = true;
            }
        }
    }

    if (pos) {
        string v = (ans_subject == "I" || ans_subject == "you") ? q_verb : (q_verb + "s");
        string res = "yes, " + ans_subject + " " + v;
        if (!q_object.empty()) res += " " + q_object;
        res += ".";
        return res;
    }
    if (neg) {
        string aux = (ans_subject == "I" || ans_subject == "you") ? "don't" : "doesn't";
        string res = "no, " + ans_subject + " " + aux + " " + q_verb;
        if (!q_object.empty()) res += " " + q_object;
        res += ".";
        return res;
    }
    return "maybe.";
}

// 2. who predicates [object] ?
string answerType2(const string& q_verb, const string& q_object, const vector<Statement>& stmts) {
    bool has_everybody = false;
    bool has_nobody = false;
    vector<string> subjects;

    for (const auto& s : stmts) {
        if (s.verb == q_verb && s.object == q_object) {
            if (!s.is_negative) {
                if (s.subject == "everybody") {
                    has_everybody = true;
                } else {
                    bool found = false;
                    for (const auto& sub : subjects) {
                        if (sub == s.subject) { found = true; break; }
                    }
                    if (!found) subjects.push_back(s.subject);
                }
            } else {
                if (s.subject == "nobody") {
                    has_nobody = true;
                }
            }
        }
    }

    if (has_everybody) {
        string res = "everybody " + q_verb + "s";
        if (!q_object.empty()) res += " " + q_object;
        res += ".";
        return res;
    }

    if (!subjects.empty()) {
        vector<string> mapped;
        for (const auto& sub : subjects) {
            if (sub == "I") mapped.push_back("you");
            else if (sub == "you") mapped.push_back("I");
            else mapped.push_back(sub);
        }

        string subj_str, verb_str;
        if (mapped.size() == 1) {
            subj_str = mapped[0];
            verb_str = (mapped[0] == "I" || mapped[0] == "you") ? q_verb : (q_verb + "s");
        } else {
            verb_str = q_verb;
            for (size_t i = 0; i < mapped.size(); i++) {
                if (i == 0) subj_str += mapped[i];
                else if (i == mapped.size() - 1) subj_str += " and " + mapped[i];
                else subj_str += ", " + mapped[i];
            }
        }
        string res = subj_str + " " + verb_str;
        if (!q_object.empty()) res += " " + q_object;
        res += ".";
        return res;
    }

    if (has_nobody) {
        string res = "nobody " + q_verb + "s";
        if (!q_object.empty()) res += " " + q_object;
        res += ".";
        return res;
    }

    return "I don't know.";
}

// 3. what does subject do ?
string answerType3(const string& q_subject, const vector<Statement>& stmts) {
    string ans_subject = (q_subject == "I") ? "you" : (q_subject == "you" ? "I" : q_subject);

    vector<string> items;
    vector<pair<string, string>> seen_act;

    for (const auto& s : stmts) {
        if (s.subject == q_subject || s.subject == "everybody" || s.subject == "nobody") {
            pair<string, string> act = {s.verb, s.object};
            bool seen = false;
            for (const auto& a : seen_act) {
                if (a == act) { seen = true; break; }
            }
            if (seen) continue;
            seen_act.push_back(act);

            string item;
            if (s.is_negative) {
                string aux = (ans_subject == "I" || ans_subject == "you") ? "don't" : "doesn't";
                item = aux + " " + s.verb;
            } else {
                string v = (ans_subject == "I" || ans_subject == "you") ? s.verb : (s.verb + "s");
                item = v;
            }
            if (!s.object.empty()) {
                item += " " + s.object;
            }
            items.push_back(item);
        }
    }

    if (items.empty()) {
        return "I don't know.";
    }

    string res = ans_subject + " ";
    if (items.size() == 1) {
        res += items[0];
    } else if (items.size() == 2) {
        res += items[0] + ", and " + items[1];
    } else {
        for (size_t i = 0; i < items.size(); i++) {
            if (i == 0) res += items[i];
            else if (i == items.size() - 1) res += ", and " + items[i];
            else res += ", " + items[i];
        }
    }
    res += ".";
    return res;
}

string answerQuestion(const string& line, const vector<Statement>& stmts) {
    string s = line.substr(0, line.length() - 1); // remove '?'
    size_t sp1 = s.find(' ');
    string word1 = s.substr(0, sp1);

    if (word1 == "who") {
        string rest1 = s.substr(sp1 + 1);
        size_t sp2 = rest1.find(' ');
        string verb_token, object;
        if (sp2 == string::npos) {
            verb_token = rest1;
            object = "";
        } else {
            verb_token = rest1.substr(0, sp2);
            object = rest1.substr(sp2 + 1);
        }
        string base_verb = verb_token.substr(0, verb_token.length() - 1);
        return answerType2(base_verb, object, stmts);
    } else if (word1 == "what") {
        string rest1 = s.substr(sp1 + 1);
        size_t sp2 = rest1.find(' ');
        string rest2 = rest1.substr(sp2 + 1);
        size_t sp3 = rest2.rfind(' ');
        string subject = rest2.substr(0, sp3);
        return answerType3(subject, stmts);
    } else {
        // "do" or "does"
        string rest1 = s.substr(sp1 + 1);
        size_t sp2 = rest1.find(' ');
        string subject = rest1.substr(0, sp2);
        string rest2 = rest1.substr(sp2 + 1);
        size_t sp3 = rest2.find(' ');
        string verb, object;
        if (sp3 == string::npos) {
            verb = rest2;
            object = "";
        } else {
            verb = rest2.substr(0, sp3);
            object = rest2.substr(sp3 + 1);
        }
        return answerType1(subject, verb, object, stmts);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    string line;
    getline(cin, line); // consume remainder of the first line

    for (int d = 1; d <= T; d++) {
        cout << "Dialogue #" << d << ":\n";
        vector<Statement> stmts;
        bool contradiction = false;

        while (getline(cin, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (line.empty()) continue;

            if (line.back() == '!') {
                cout << line << "\n\n";
                break;
            } else if (line.back() == '.') {
                Statement s = parseStatement(line);
                if (!contradiction) {
                    for (const auto& prev : stmts) {
                        if (contradict(prev, s)) {
                            contradiction = true;
                            break;
                        }
                    }
                }
                stmts.push_back(s);
            } else if (line.back() == '?') {
                cout << line << "\n";
                if (contradiction) {
                    cout << "I am abroad.\n\n";
                } else {
                    string ans = answerQuestion(line, stmts);
                    cout << ans << "\n\n";
                }
            }
        }
    }

    return 0;
}