# def is_disjoint(A: list[int], B: list[int], C: list[int]) -> bool:
#     for a in A:
#         for b in B:
#             for c in C:
#                 if a == b == c:
#                     return False
#     return True

# def is_disjoint(A: list[int], B: list[int], C: list[int]) -> bool:
#     # Takes NlogN time and N additional memory.
#     sorted_A = sorted(A)
#     sorted_B = sorted(B)
#     sorted_C = sorted(C)

#     # TODO: check correctness and runtime analysis.
#     # TODO: optimization - stop the search as soon as one of the lists is exhausted.
#     idx_a, idx_b, idx_c = 0, 0, 0
#     while idx_a <= len(sorted_A) or idx_b <= len(sorted_B) or idx_c <= len(sorted_C):
#         while sorted_B[idx_b] < sorted_A[idx_a]:  # overall occurs between N and 2N times
#             idx_b += 1                            # overall occurs N times
#         while sorted_C[idx_c] < sorted_B[idx_b]:  # overall occurs between N and 2N times
#             idx_c += 1                            # overall occurs N times
#         assert(sorted_C[idx_c] >= sorted_B[idx_b] >= sorted_A[idx_a])
#         if sorted_A[idx_a] == sorted_B[idx_b] == sorted_C[idx_c]:    # overall occurs between N and 2N times (see notes below)
#             return False
#         else:
#             idx_a += 1                            # overall occurs N times
#     return True

def is_disjoint(A: list[int], B: list[int], C: list[int]) -> bool:
    counts = {}
    def add_elems_to_counts(lst: list[int]) -> None:
        nonlocal counts
        for elem in lst:
            if elem in counts:
                counts[elem] += 1
            else:
                counts[elem] = 1
    add_elems_to_counts(A)
    add_elems_to_counts(B)
    add_elems_to_counts(C)
    for count in counts.values():
        if count == 3:
            return False
    return True

# def is_disjoint(A: list[int], B: list[int], C: list[int]) -> bool:
#     for a in A:
#         for b in B:
#             if a == b:  # this check occurs O(N^2) times.
#                 # the check passes *at most* N times because of the uniqueness assumption above.
#                 for c in C:
#                     if c == a:
#                         return False
#     return True
