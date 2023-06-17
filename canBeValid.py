class Solution:
    def canBeValid(self, s: str, locked: str) -> bool:
        if (len(s) & 1):
            return False
        locked = [1 if ch == '1' else 0 for ch in locked]
        st = []
        for i, ch in enumerate(s):
            if ch == ')':
                if st:
                    if st[-1][0] == '(':
                        st.pop()
                    else:
                        if locked[st[-1][1]]:
                            return False
                        else:
                            st.pop()
                else:
                    if locked[i]:
                        return False
                    else:
                        st.append(('(', i))
                        locked[i] = 1
            else:
                st.append(('(', i))
        if st:
            if len(st) & 1:
                return False
            for _ in range(len(st) // 2):
                ch, i = st.pop()
                if ch == ')' or locked[i]:
                    return False
            return True
        return True


def main():
    sol = Solution()
    arg1 = "())()))()(()(((())(()()))))((((()())(())"
    arg2 = "1011101100010001001011000000110010100101"
    print(sol.canBeValid(arg1, arg2))


main()
