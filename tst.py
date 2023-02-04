

t = int(input())
for i in range(t):
    arr = []
    n = int(input())
    a = [int(k) for k in input().split()]
    s = sum(a)
    max = 0
    a = sorted(a)
    for k in a:
        if k < 0 :
            arr.append(k)
        else:
            if len(arr) % 2 == 0:
                break
            else :
                if k <= -arr[-1]:
                    s -= 2*k
                else:
                    s += 2*arr[-1]
                break
    if len(arr) == len(a):
        if len(arr) % 2 :
            print(-sum(arr) + 2 *arr[-1])
        else :
            print(-sum(arr))
    else:
        print(s - 2*sum(arr))