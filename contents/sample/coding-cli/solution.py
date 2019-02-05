import sys

def main(argv):
  a_obj = map(int, argv[1:])

  a = []
  for v in a_obj:
    a.append(v)
  print(str(min(a))+" "+str(max(a)))

  ints = ""
  a.sort()
  for v in a:
    ints += str(v)
  print(ints)

if __name__ == '__main__':
  main(sys.argv[1:])

