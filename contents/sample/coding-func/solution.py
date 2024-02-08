def sort_and_concat_integers(n: int, a: list[int]) -> str:
    a_sorted = sorted(a)
    return ''.join(map(str, a_sorted))
