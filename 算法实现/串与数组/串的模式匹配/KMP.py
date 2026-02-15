def KMP(pattern, str):
    # 将模式串和文本串连接起来，使用特殊字符分隔，避免匹配时出现重叠
    combine = pattern + "#" + str
    # 第一个位置的最长公共前后缀长度为0
    pi = [0, ]

    for i in range(1, len(combine)):
        # 获取前一个位置的最长公共前后缀长度
        prev = pi[i - 1]

        # 如果当前字符与前一个位置的最长公共前后缀的下一个字符不匹配，则继续回退到更短的公共前后缀
        while prev > 0 and combine[i] != combine[prev]:
            prev = pi[prev - 1]

        # 如果当前字符与前一个位置的最长公共前后缀的下一个字符匹配，则最长公共前后缀长度加1
        if combine[i] == combine[prev]:
            if i > len(pattern) and prev + 1 == len(pattern):
                return i - 2 * len(pattern)  # 匹配成功，返回主串中匹配的起始位置
            pi.append(prev + 1)
        # 否则最长公共前后缀长度为0
        else:
            pi.append(0)


if __name__ == '__main__':
    pattern = "abaabc"  # 模式串
    str = "abaabaabacacaabaabcc"  # 主串

    print(KMP(pattern, str))
