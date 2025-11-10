import re
import sys
import os 

# --- 第 1 步：编辑这一行 ---
YOUR_STUDENT_ID = "A0311920U"  # 将这里替换成你自己的学生 ID
# ---

INPUT_FILE = "train.txt"

def parse_my_data(student_id, file_path):
    """
    解析 train.txt 以查找学生的数据并打印 C++ 代码。
    如果找不到学生 ID，则打印错误并退出。
    """
    letter_to_int = {chr(ord('A') + i): i for i in range(10)}
    
    try:
        # 使用 'utf-8-sig' 自动处理文件开头的 BOM 字符
        with open(file_path, 'r', encoding='utf-8-sig') as f:
            lines = f.readlines()
    except FileNotFoundError:
        print(f"错误：找不到 '{file_path}'。")
        print("请将此脚本与 train.txt 放在同一个文件夹中。")
        sys.exit(1) 

    student_found = False
    headers = []
    cpp_edges = []
    source_city = ""
    dest_city = ""
    found_block_for_id = False 

    for i, line in enumerate(lines):
        
        # --- 强力清理 ---
        # 1. 移除 (U+00A0) 不间断空格
        line = line.replace('\u00A0', ' ') 
        # 2. 移除 (U+FEFF) 零宽度不换行空格 (BOM)
        # lstrip() 只移除开头的匹配项
        line = line.lstrip('\uFEFF')
        # 3. 移除行首/行尾的所有空白
        clean_line_strip = line.strip()
        # 4. 创建一个用于检查的小写版本
        clean_line_lower = clean_line_strip.lower()
        # ---------------------------

        # 检查 StudentID (保持大小写敏感)
        if clean_line_strip.startswith("StudentID:"):
            parts = clean_line_strip.split()
            if len(parts) >= 2 and parts[1] == student_id:
                student_found = True
                found_block_for_id = True 
                continue 

        # 如果我们正在查找特定 ID 的块
        if found_block_for_id:
            # 检查标题行 (例如 "A   B   C ... J")
            if not headers and clean_line_strip.startswith("A") and clean_line_strip.endswith("J"):
                headers = clean_line_strip.split() 
                headers = [h.strip() for h in headers if h.strip() in letter_to_int]
                continue

            # 检查数据行 (例如 "A   74 ...")
            if headers and re.match(r"^[A-J]", clean_line_strip):
                # 假设数据是制表符分隔的
                parts = clean_line_strip.split('\t')
                
                from_city = parts[0].strip()
                if from_city not in letter_to_int:
                    continue 
                    
                from_index = letter_to_int[from_city]
                
                for j, time_str in enumerate(parts[1:], start=0):
                    # 检查数字，移除周围空格
                    if j < len(headers) and time_str.strip().isdigit():
                        to_city = headers[j]
                        if to_city in letter_to_int:
                            to_index = letter_to_int[to_city]
                            time = int(time_str.strip())
                            cpp_edges.append(f"    g.addEdge({from_index}, {to_index}, {time}); // {from_city} -> {to_city}")
            
            # --- 最终修复：使用 'in' 和 'lower()' 进行不区分大小写的检查 ---
            if "source" in clean_line_lower:
                parts = clean_line_strip.split() # 按任意空白分割
                if len(parts) >= 2:
                    source_city = parts[-1]
            
            if "destination" in clean_line_lower:
                parts = clean_line_strip.split() # 按任意空白分割
                if len(parts) >= 2:
                    dest_city = parts[-1]
            # -------------------------------------------------------------

            # 检查块结束符
            if "--------------------------------" in line:
                break # 找到了当前 ID 的所有数据，停止解析

    # --- 错误处理 ---
    if not student_found:
        print(f"错误：在 '{file_path}' 中找不到学生 ID '{student_id}'。")
        print("请检查 YOUR_STUDENT_ID 变量是否正确。")
        sys.exit(1) 
        
    if not source_city or not dest_city:
        print(f"错误：找到了学生 ID '{student_id}'，但未能解析其 Source 或 Destination 城市。")
        print("这几乎可以肯定是您本地 train.txt 文件中的编码或不可见字符问题。")
        print("请尝试：重新从 Coursemology 下载 train.txt，或者在一个纯文本编辑器中打开并重新保存为 'UTF-8' 编码。")
        sys.exit(1)
    
    if not cpp_edges:
        print(f"错误：找到了学生 ID '{student_id}'，但未能解析任何图的边 (Edges)。")
        print("这很可能是 train.txt 的数据行格式问题。")
        sys.exit(1)

    if source_city not in letter_to_int or dest_city not in letter_to_int:
        print(f"错误：解析到的 Source '{source_city}' 或 Destination '{dest_city}' 不是有效的城市名称 (A-J)。")
        sys.exit(1)
    
    # --- 打印 C++ 代码 ---
    print(f"// --- 为学生 ID 自动生成的 C++ 代码：{student_id} ---")
    print("// 将此代码复制并粘贴到 train_solver.cpp 的 main() 函数中")
    print("\n")
    print(f"    char source_letter = '{source_city}';")
    print(f"    char dest_letter = '{dest_city}';")
    print(f"    int source = {letter_to_int[source_city]};")
    print(f"    int dest = {letter_to_int[dest_city]};")
    print("\n    // --- 定义图的边 ---")
    cpp_edges.sort() 
    for edge_line in cpp_edges:
        print(edge_line)
    print("\n    // --- 自动生成的代码结束 ---")


if __name__ == "__main__":
    if YOUR_STUDENT_ID == "请在这里输入你的学生ID":
        print("错误：请先编辑此 Python 文件，将 YOUR_STUDENT_ID 变量设置为你的学生 ID。")
        sys.exit(1)
        
    try:
        script_dir = os.path.dirname(__file__)
    except NameError: 
        script_dir = '.'
    
    file_path = os.path.join(script_dir, INPUT_FILE)
    
    parse_my_data(YOUR_STUDENT_ID, file_path)