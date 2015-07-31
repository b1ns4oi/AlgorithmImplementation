
class Treenode:
	def __init__(self, x):
		self.val = x
		self.left = None
		self.right = None

	def p(self):
		print(self.val)
		if self.left:
			self.left.p()
		if self.right:
			self.right.p()


class Solution():
	# [start, end)
	def reconstruct(self, l, start, end):
		print('start={}'.format(start))
		print('end={}'.format(end))
		print()
		if start == end:
			return None

		n = Treenode(l[start])
		mid = end
		for i, val in enumerate(l[start:end]):
			if val > l[start]:
				mid = i+start
				break
		print('mid={}'.format(mid))
		print()

		n.left = self.reconstruct(l, start+1, mid)
		n.right = self.reconstruct(l, mid, end)
		return n

if __name__ == '__main__':
	l = [30, 20, 10, 21, 50, 40, 60]
	s = Solution()
	n = s.reconstruct(l, 0, len(l))
	n.p()

