import sys
sys.path.append('/root/py/build')
import example_module

# 创建一个 Example 对象
example = example_module.Example(10)
print(example.getValue())  # 输出: 10

# 修改 Example 对象的值
example.setValue(20)
print(example.getValue())  # 输出: 20
