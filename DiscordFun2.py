import random

start = {"1234"}
users = {}
dig = 4


def build():
    # global start
    for i in range(1, 10**dig):
        s = str(i).zfill(dig)
        temp = ''.join(sorted(s))
        if len(set(temp)) == dig:
            start.add(s)


def ok(s, key):
    for i in range(dig):
        if ord(key[i]) < ord('A') and key[i] != s[i] or ord(
                key[i]) >= ord('A') and s.find(
                    chr(ord(key[i]) - ord('A') + ord('0'))) != -1:
            return False
    return True


def build2(s, num, p, d, f, poss, notTaken):
    if p == dig:
        if d == 0 and f == 0:
            temp = list(notTaken)
            for i in range(dig):
                if s[i] == 'X' and temp:
                    a = 1
                    s = s[:i] + chr(ord('A') + int(temp.pop())) + s[i + 1:]
            poss.append(s)
        return
    if d:
        for i in range(dig):
            if i == p or s[i] != 'X':
                continue
            c = s[i]
            s = s[:i] + num[p] + s[i + 1:]
            notTaken.discard(num[p])
            build2(s, num, p + 1, d - 1, f, poss, notTaken)
            s = s[:i] + c + s[i + 1:]
            notTaken.add(num[p])
    if f and s[p] == 'X':
        c = s[p]
        s = s[:p] + num[p] + s[p + 1:]
        notTaken.discard(num[p])
        build2(s, num, p + 1, d, f - 1, poss, notTaken)
        s = s[:p] + c + s[p + 1:]
        notTaken.add(num[p])
    build2(s, num, p + 1, d, f, poss, notTaken)

def update(s, d, f, ss):
    modify = 1
    poss = []
    imp = set()
    X = 'X' * dig
    st = set(s)
    # print(st)
    build2(X, s, 0, d, f, poss, st)
    if poss and poss[0] == X:
        imp.update(s)
    cnt = 0
    itrs = []
    for str_ in ss:
        if d + f < dig and str_ == s:
            cnt += 1
            if modify:
                itrs.append(str_)
            continue
        check = False
        if imp:
            for char in str_:
                if char in imp:
                    check = True
                    break
            if check:
                cnt += 1
                if modify:
                    itrs.append(str_)
                continue
        for key in poss:
            if ok(str_, key):
                check = True
                break
        if not check:
            cnt += 1
            if modify:
                itrs.append(str_)
    if modify:
        for it in itrs:
            ss.discard(it)
    return cnt


def find(num, guess):
    d, f = 0, 0
    s = set(num)
    for i in range(dig):
        if num[i] == guess[i]:
            f += 1
            d -= 1
    for c in guess:
        if c in s:
            d += 1
    return (d, f)


def worst(num, ss):
    res, done = -1, 4
    mpp = {}
    cnt = -1
    for it in ss:
        p = find(num, it)
        p2 = p[0] * 5 + p[1]
        if p2 not in mpp:
            mpp[p2] = 0
        mpp[p2] += 1
        val = mpp[p2]
        if val > cnt or (val == cnt and res == done):
            cnt = val
            res = p2
    if len(mpp) > 5 and random.randint(0, 1):
        del mpp[res]
        if done in mpp:
            del mpp[done]
        cnt = -1
        for it in mpp:
            if mpp[it] > cnt:
                cnt = mpp[it]
                res = it
    return (res // 5, res % 5)


def guess(text, num):
    if text.author.id not in users:
        users[text.author.id] = start
        update(num, 1, 0, users[text.author.id])
        return (1, 0)
    t = worst(num, users[text.author.id])
    update(num, t[0], t[1], users[text.author.id])
    print(len(users[text.author.id]))
    return (t[0], t[1])


def getRand(text):
    res = random.choice(tuple(users[text.author.id]))
    if text.author.id in users:
        del users[text.author.id]
    print("size of users =", len(users))
    return res
