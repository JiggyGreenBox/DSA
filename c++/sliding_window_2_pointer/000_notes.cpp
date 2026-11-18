/*
======================================
sliding window notes
======================================

    prefix array is for queries on the sum between 2 idx's

    sum(i,j) = prefix[j] - prefix[i-1]
    right shift by 1 for prefix array
    sum(i,j) = prefix[j+1] - prefix[i]

    how to build

    f(nums)
        vector<int> prefix(n+1)
        for i ..n
            prefix[i+1] = prefix[i] + nums[i]

======================================
fixed window

    max avg of len k
        k is constant for each window
        then we want max-sum for window k
            for i=0 i<k
                sum = add(num)

            max_sum = sum
            for k..n-1
                remove(i-k)
                add(i)
                sum = 
                track max_sum

        return max_sum / k

    
    max vowels
        isvowel helper
        same as above


    max points from cards
        [1 2 3 .....     8 9 10]

        if k is 3
            we can take 1 2 3, or we can take 1,2 and 10
            or 1 and 9, 10

        so we get leftsum
        and look for a better sum by removing from left
            and adding right

        for i=0, i<k 
            left_sum =

        max = left_sum

        for i=1; i<=k
            remove nums[k-i]    need to remove k-1..0
            add nums[n-i]       need to add n-1..n-k-1
            sum = 
            max = 

        return max

======================================
        
    min size subarray sum that is >= k

        left = 0
        for right 0..n-1

            sum = add num

            while sum >= k
                min-len = 
                remove left
                left++

        return min-len == INT_MIN or min-len

======================================    

    longest substring with no repeating chars

        if we see a char we cant see it again
            the substring is invalid

        we store char by using a set or a count array
            then we use while to shrink till valid

        what we see is that the valid idx is +1 of the duplicated element
            a,b,c,d,e,b,.....
            0 1 2 3 4 5

            L         R

            when R reaches 5(b), we shrink L till 2(c)
                because the b is at 1

            instead we store idx
            then we jump to seen[idx] + 1

        
        vector<int> seen(26, -1); // -1, since left starts at 0
        left=0

        right 0..n-1
            int idx = str[right] - 'a'
                map a to 0
                    b to 1 
                    ...

            if seen[idx] >= left        duplicate char found
                left = seen[idx]+1

            seen[idx] = right
            len = right - left + 1
            track max
            
======================================    

    fruits in a basket

        we want max trees
            trees have types
                only 2 types are allowed
                    the third type makes the collection invalid

            return max-trees, longest-subarray

        longest-subarray with distinct nums == 2
            we need map
                type, count

            expand till map.size <= 2
            then remove from front
                till size <= 2

            track size when valid window

======================================

longest substring with k distinct

    with 1 dup u can jump
        with k distince how will u jump
            not possible

    count[256] = 0
    left = 0
    for right .. n-1
        int ch-idx = s[r] - 'a'

        if count[ch-idx] > 0
            distinct++

        while(distinct > k)
            int left-idx = s[left] - 'a'
            count[left_idx]--
            if(count[left_idx] == 0)
                distinct--

        track right - left + 1

    
    a small optim
        instead of while use if

        return n-left

======================================

longest repeating substring with k char replacements allowed
    whatever is the longest freq, we are allowed k replacements

    aaaxxa, k=2
        replace 2x with a
        len is 6

    need to track max-freq
    then len-maxfreq <=k is valid

    left=0
    max-freq
    right 0..n-1
        mpp[ch]++

        max-freq = max(max-freqm, mpp[ch])

        while(right-left+1 - max-freq > k)
            mpp[s[l]]--
            l++

        max-len = ...


    we can use if/while
        n-left / max at each iter

======================================

binary subarrays with sum

    atMost logic
        sliding windows work on monotonic property of sum
        this means only positive numbers

        n^2 gives us each subarray and we can query this

        [l..r] we know it has some sum
        evey subarray of this has a value <= sum
            because all numbers are +ve

        to find COUNT of subarrays with exact sum
            we can find all subarrays with sum <= goal and sum <= goal-1

            we will remain will exactly k
                [1,1,3]
                    goal = 3
                    subs with sum <= goal = [1,1,3]
                                                [1], [1,1],[1] [3]
                                                    4
                    subs with sum <= goal-1 = [1,1]
                                                [1], [1,1],[1]
                                                    3
                    only [3] remains

        
        for a valid range
            [1,2,3]
                we count all sub arrays ending at cur idx
                    [1,2,3], [2,3], [3]
                this becomes
                    total += len

                think of this as backward counting

            and as we move forwards
                we automatically forwards count
                at 
                    [1,2]
                        [2]
                            what about [1]?
                                it was counted when we started at idx-0

            atMost(nums, goal) {

                left = 0;
                sum = 0;
                total = 0;
                
                right 0..n-1

                    sum += nums[right];

                    while(sum > goal) {
                        sum -= nums[left];
                        left++;
                    }
                    total += right - left + 1;
                
                return total;
            }

======================================

nice subarrays
    instead of sum we increase count when we find an odd number
        if num & 1
            count++

        while / if count > k
            if num[left]&1
                count--
            left++

        maxlen = ...
    maxlen / (n-left)

======================================

Minimum Window Substring

    target, t
    source, s

    we need all chars of t in s
        in the smallest substring

    need all chars of t
        remaining = t.size
        need all counts of chars as well
            count[26] = each char of t

    then
        for a window
            if char[s] > 0
                remaining--
            count[s]--        t char becomes 0, non-t becomes -1

        if remaining == 0
            all chars found
            store len 
                (assign start to return substring)
                push left ahead

            count[left]++
            left++
                        
            if count[left] > 0      tchar becomes >0, non-t becomes 0
                remaining++

    return min-len


    what if we need the substring and not just len
    then return s.substring(start, min-len)
        where do we store start,
            with min-len update



======================================

Permutation in a string
    find "ab" in "eidbaooo"
        true as "ba"

    find "ab" in "eidboaoo"
        false window is 3 chars
    we need a fixed window of size t

    remaining = ...
    for each t
        count[ch]++

    for i till t window
        check remaining

    if remaining == 0
        return true

    for right till end
        remove char
        add add
        check remaining
            ret true if 0

======================================

find all anagrams of a string
    given a target t
    find all starting points when some combination of chars are found

    we need a fixed window of size t
    we need remaining = s.size
    we need count[ch] of t

    int rem = t.size
    int k(window-size) = t.size

    for right=0; right<n

        if count[ch] > 0
            count[ch]--
            remaining--

        if right >=k
            remove [right-k]
            if(count[right-k] >= 0)
                remaining--
            count[right-k]--

        if remaining == 0
            store
            right-k+1
                why?
                len = right-left+1
                left = right-len+1

======================================

Longest subarray containing at most k zeros.

    Invariant:
    window has <= k zeros.

        if num == 0
            zeros++

        while / if zeros > k:
            shrink from left until valid.
            if nums[left] == 0
                zeros--
            left++

        max-len = ..
    return max-len / (n-left)

======================================

Minimum_Operations_to_Reduce_X_to_Zero
    we can remove elements from the front or the back
    which means only a subarray remains

    we want [1,2,3....5,6,7] x=10
        either remove start/ending at each step which reduces from x=10 till x=0

    we want
        total - subarray = x
        subarray = total-x
        find longest subarray to have least removals

        removals is n-len(subarray)

    target = total-x
    find longest subarray len with target
        add sum
        while sum> target
            remove

        if sum == target 
            update max-len

    return n-max-len

    this if/while is used when we want sum>= and not when sum==

======================================

numberOfSubstrings with 3 chars a,b,c

    count(3, 0)
    l=0
    for r [0..n-1]
        count[ch-a]++

        while(count[0] > 0 && count[1] > 0 && count[2] > 0) {
            everysubstring till the end is valid
            ans += n-r; 
            count[l]--
            l++
        }

======================================

count subarrays with k distinct chars
    when we see count, we should think atMost
    len of substring is different from counting

    use count[] to check distinct
        a new distinct char will have count==0 before being added

    expand window till valid, when invalid shrink
        while distinct > k
            count[left-ch]--
            if count == 0
                distinct--

        total += right-left+1
        
======================================
*/  