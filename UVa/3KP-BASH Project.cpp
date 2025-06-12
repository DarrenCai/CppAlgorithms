/**
 * UVa10966
 * 简单的Bash
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

#define ULL unsigned long long

const string no_such_command = "no such command", bad_usage = "bad usage", path_not_found = "path not found",
             file_not_found = "file not found", dir_exists = "a directory with the same name exists",
             f_dir_exists = "file or directory with the same name exists", empty_l = "[empty]";
struct params {ULL size = 0; bool r = false, h = false, s = false, S = false, f = false, d = false;};
struct file {
    string name, full_path; int parent; ULL size; bool dir, hidden; vector<int> sub;
    file(const string& name, const string& full_path, int parent, ULL size = 0, bool dir = false, bool hidden = false)
    :name(name), full_path(full_path), parent(parent), size(size), dir(dir), hidden(hidden) {};
};
vector<file> fs; int curr_dir;

void trim(string& s) {
    int l, r, t = s.size();
    for(l=0; l<t; ++l) if(!isspace(s[l])) break;
    for(r=t-1; r>l; --r) if(!isspace(s[r])) break;
    s = s.substr(l, r-l+1);
}

bool valid_path(const string& s, int& dir, string& name, bool pre = true) {
    vector<string> p; dir = s[0] == '/' ? 0 : curr_dir;
    if (!s.empty() && s.back() == '/') pre = false;
    for (int i=0, h=0, t=s.size(); i<t; ++i) {
        if (s[i] == '/') {
            if (i > 0 && s[i-1] != '/') p.push_back(s.substr(h, i-h));
            h = i+1;
        } else if (i+1 == t) p.push_back(s.substr(h, t-h));
    }
    for (int i=0, t=p.size()-pre; i<t; ++i) {
        if (p[i] == ".") continue;
        if (p[i] == "..") {
            if (fs[dir].parent < 0) return false;
            dir = fs[dir].parent;
        } else {
            const vector<int>& sub = fs[dir].sub; bool ok = false;
            for (int j=sub.size()-1; j>=0; --j) if (fs[sub[j]].name == p[i]) {
                if (fs[sub[j]].dir) dir = sub[j], ok = true;
                break;
            }
            if (!ok) return false;
        }
    }
    name = p.empty() || s.back() == '/' ? "" : p.back();
    return true;
}

bool valid_name(const string& s) {
    if (s.empty() || s.size() > 255) return false;
    for (int i=0, t=s.size(); i<t; ++i)
        if ((s[i]=='.' && (t==1 || (s[i+1]=='.'))) || (s[i]!='.' && !isalpha(s[i]) && !isdigit(s[i]))) return false;
    return true;
}

bool cmp_p(int i, int j) {
    return fs[i].full_path < fs[j].full_path;
}

bool cmp_s(int i, int j) {
    return fs[i].size < fs[j].size || (fs[i].size == fs[j].size && fs[i].full_path < fs[j].full_path);
}

bool cmp_S(int i, int j) {
    return fs[i].size > fs[j].size || (fs[i].size == fs[j].size && fs[i].full_path < fs[j].full_path);
}

void visit_fs(int dir, vector<int>& out, const string& name, bool r, bool h, bool d = true, bool f = true) {
    for (int i=0, t=fs[dir].sub.size(); i<t; ++i) {
        const file& fi = fs[fs[dir].sub[i]];
        if ((!fi.hidden || h) && ((fi.dir && d) || (!fi.dir && f)) && (name.empty() || fi.name == name))
            out.push_back(fs[dir].sub[i]);
        if (fi.dir && r) visit_fs(fs[dir].sub[i], out, name, r, h, d, f);
    }
}

string info(const file& f) {
    ostringstream ss; ss << f.full_path << ' ' << f.size;
    if (f.hidden) ss << " hidden";
    if (f.dir) ss << " dir";
    return ss.str();
}

void new_session() {
    fs.clear(); fs.push_back(file("", "/", -1, 0, true)); curr_dir = 0;
}

void cd(const string& mp, vector<string>& out) {
    int dir; string name;
    if (!valid_path(mp, dir, name, false)) return out.push_back(path_not_found);
    curr_dir = dir;
}

void touch(const string& mp, const params& p, vector<string>& out) {
    int dir; string name;
    if (!valid_path(mp, dir, name)) return out.push_back(path_not_found);
    if (!valid_name(name)) return out.push_back(bad_usage);
    for (int i=fs[dir].sub.size()-1; i>=0; --i) if (fs[fs[dir].sub[i]].name == name) {
        if (fs[fs[dir].sub[i]].dir) return out.push_back(dir_exists);
        fs[fs[dir].sub[i]].size = p.size; fs[fs[dir].sub[i]].hidden = p.h;
        return;
    }
    file fi(name, (dir ? fs[dir].full_path + '/' : "/") + name, dir, p.size, false, p.h);
    int s = fs.size(); fs[dir].sub.push_back(s); fs.push_back(fi);
}

void mkdir(const string& mp, const params& p, vector<string>& out) {
    int dir; string name;
    if (!valid_path(mp, dir, name)) return out.push_back(path_not_found);
    if (!valid_name(name)) return out.push_back(bad_usage);
    for (int i=fs[dir].sub.size()-1; i>=0; --i) if (fs[fs[dir].sub[i]].name == name)
        return out.push_back(f_dir_exists);
    file fi(name, (dir ? fs[dir].full_path + '/' : "/") + name, dir, 0, true, p.h);
    int s = fs.size(); fs[dir].sub.push_back(s); fs.push_back(fi);
}

void find(const string& mp, const params& p, vector<string>& out) {
    int dir; string name;
    if (!valid_path(mp, dir, name)) return out.push_back(path_not_found);
    vector<int> res;
    visit_fs(dir, res, name, p.r, p.h);
    if (res.empty()) return out.push_back(file_not_found);
    sort(res.begin(), res.end(), cmp_p);
    for (int i=0, t=res.size(); i<t; ++i) out.push_back(info(fs[res[i]]));
}

void ls(const string& mp, const params& p, vector<string>& out) {
    int dir; string name;
    if (!valid_path(mp, dir, name, false)) return out.push_back(path_not_found);
    vector<int> res;
    visit_fs(dir, res, "", p.r, p.h, !p.f, !p.d);
    if (res.empty()) return out.push_back(empty_l);
    sort(res.begin(), res.end(), p.s ? cmp_s : (p.S ? cmp_S : cmp_p));
    for (int i=0, t=res.size(); i<t; ++i) out.push_back(info(fs[res[i]]));
}

void run_command(const string& cmd, vector<string>& out) {
    if (cmd.empty()) return;
    istringstream ss(cmd); string s; ss >> s;
    if (s != "cd" && s != "touch" && s!= "mkdir" && s != "find" && s != "ls" && s != "pwd" && s != "exit" && s != "grep") {
        out.push_back(no_such_command);
    } else {
        string mp; params p; ULL v; string s1; ss >> s1;
        while (!s1.empty()) {
            if (s1[0] == '-') {
                if (isalpha(s1[1])) {
                    if (s1[1] == 'r') p.r = true;
                    else if (s1[1] == 'h') p.h = true;
                    else if (s1[1] == 'd') p.d = true;
                    else if (s1[1] == 'f') p.f = true;
                    else if (s1[1] == 's') p.s = true;
                    else if (s1[1] == 'S') p.S = true;
                } else if (istringstream(s1.substr(1)) >> v) p.size = v;
                else return out.push_back(bad_usage);
            } else if (!mp.empty()) return out.push_back(bad_usage);
            else mp = s1;
            s1.clear(); ss >> s1;
        }
        if (s == "cd") mp.empty() ? out.push_back(bad_usage) : cd(mp, out);
        else if (s == "touch") mp.empty() ? out.push_back(bad_usage) : touch(mp, p, out);
        else if (s == "mkdir") mp.empty() ? out.push_back(bad_usage) : mkdir(mp, p, out);
        else if (s == "find") mp.empty() ? out.push_back(bad_usage) : find(mp, p, out);
        else if (s == "ls") ls(mp, p, out);
        else if (s == "pwd") out.push_back(mp.empty() ? fs[curr_dir].full_path : bad_usage);
        else if (s == "grep" || (s == "exit" && !mp.empty())) out.push_back(bad_usage);
        else new_session();
    }
}

void run_cmdline(const string& line) {
    vector<string> cmds, out;
    for (int i=0, t=line.size(), s=0, q=0; i<=t; ++i) if (i==t || (line[i] == '|' && !q)) {
        cmds.push_back(string(line.begin()+s, line.begin()+i)); s = i+1;
    } else if (line[i] == '"') q ^= 1;
    if (cmds.empty()) return;
    run_command(cmds[0], out);
    for (int i=1, t=cmds.size(); i<t; ++i) {
        istringstream ss(cmds[i]); string s, p; ss >> s; getline(ss, p); trim(p);
        if (s != "grep" || p.size() < 2 || p[0] != '"' || p.back() != '"') {
            cout << bad_usage << endl;
            return;
        }
        if (out.empty() || p.size()==2) continue;
        vector<string> filtered; s = p.substr(1, p.size()-2);
        for (int j=0, k=out.size(); j<k; ++j) if (out[j].find(s) != string::npos) filtered.push_back(out[j]);
        out.swap(filtered);
    }
    for (int i=0, t=out.size(); i<t; ++i) cout << out[i] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    string line; new_session();
    while (getline(cin, line)) run_cmdline(line);
    return 0;
}