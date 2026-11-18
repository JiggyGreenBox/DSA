/*
======================================================================
prefix array
    prefix.resize(n+1)

    for i [0..n-1]
        prefix[i+1] = prefix[i] + nums[i]

    query sum(i,j)
        return prefix[j+1] - prefix[i]

======================================================================
find pivot index
    find the idx, where leftsum == rightsum, not counting num[idx]

    we want     
        sum(0,i-1) == sum(i+1,n-1)

        we use a prefix array
            sum(0,i-1) = prefix[i] - prefix[0]
                       = prefix[i] (sum till x, not counting x)

            sum(i+1, n-1) = prefix[n] - prefix[i+1]
                          = total - (sum with x)

        we want
            leftsum == total - lefsum + num

    total = accumulate
    leftsum = 0
    for 0..n-1
        if leftsum = total - leftsum + num
            return idx

        leftsum += num
    return -1

======================================================================


======================================================================
======================================================================
======================================================================

*/