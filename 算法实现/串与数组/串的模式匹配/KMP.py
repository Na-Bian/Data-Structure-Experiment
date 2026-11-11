def KMP(pattern, text):
    if pattern == "":
        return 0

    # 分隔符必须不出现在两个原始字符串中
    combine = pattern + "#" + text
    pi = [0] * len(combine)
    # 保存当前最长相同前后缀长度
    j = 0 

    m = len(pattern)

    for i in range(1, len(combine)):

        # 失配时，回退到更短的公共前后缀
        while j > 0 and combine[i] != combine[j]:
            j = pi[j - 1]

        # 匹配成功时，长度增加
        if combine[i] == combine[j]:
            j += 1

        pi[i] = j

        # 在主串部分匹配到整个模式串
        if i > m and pi[i] == m:
            return i - 2 * m

    return -1


pattern = "abaabc"
text = "abaabaabacacaabaabcc"

print(KMP(pattern, text))  # 13
