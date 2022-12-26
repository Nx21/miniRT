def solution(l):
    s = sum(l)
    if s % 3 == 0:
        l = sorted(l, reverse=True)
        res = ""
        for i in l:
            res += str(i)
        return res
    l = sorted(l)
    ok = 0
    for i in list(l):
        if i%3 == s%3:
            ok = 1
            l.remove(i)
            break
    if ok :
        l = sorted(l, reverse=True)
        res = ""
        for i in l:
            res += str(i)
        return res
    ok = 0
    for i in list(l):
        if i%3 == 3 - s%3:
            ok += 1
            l.remove(i)
        if ok == 2:
            break
    l = sorted(l, reverse=True)
    res = ""
    for i in l:
        res += str(i)
    return res

print(solution([ 3,1, 6, 1]))