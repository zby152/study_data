from flask import Flask, redirect, request, render_template, url_for, session, send_file
import os
import io
import time
from mode import *

app = Flask(__name__)
app.secret_key = os.urandom(24)


# 加密页面
@app.route('/', methods=['GET', 'POST'])
def encrypt():
    if request.method == 'POST':
        file = request.files['fileInput']
        key = request.form['keyInput']
        mode = request.form['mode']
        block_mode = request.form['block_mode']

        if not file or not key:
            return render_template('encode.html', error='No file or key provided')

        file_content = file.read()

        result = ''
        start_time=time.time()
        if mode == 'ECB' and block_mode == 'PAD':
            messages, remainder = read_file(file_content)
            result = EN_ECB_PAD(messages, remainder, key)

        if mode == 'CBC' and block_mode == 'PAD':
            messages, remainder = read_file(file_content)
            result = EN_CBC_PAD(messages, remainder, key)

        if mode == 'ECB' and block_mode == 'STE':
            messages, remainder = read_file(file_content)
            result, remainder = EN_ECB_STE(messages, remainder, key)
            session['remainder'] = remainder

        if mode == 'CBC' and block_mode == 'STE':
            messages, remainder = read_file(file_content)
            result, remainder = EN_CBC_STE(messages, remainder, key)
            session['remainder'] = remainder
        end_time = time.time()
        run_time=end_time-start_time
        # 将加密结果转换为适合存储在session中的格式
        session['result'] = result
        session['block_mode'] = block_mode
        session['run_time']=run_time

        return redirect(url_for('en_result'))

    return render_template('encode.html')


# 解密页面
@app.route('/decode', methods=['GET', 'POST'])
def decode():
    if request.method == 'POST':
        file = request.files['fileInput']
        key = request.form['keyInput']
        mode = request.form['mode']
        block_mode = request.form['block_mode']

        if not file or not key:
            return render_template('encode.html', error='No file or key provided')

        file_content = file.read()

        result = ''
        start_time = time.time()
        if mode == 'ECB' and block_mode == 'PAD':
            messages, remainder = read_file(file_content)
            result = DE_ECB_PAD(messages, remainder, key)

        if mode == 'CBC' and block_mode == 'PAD':
            messages, remainder = read_file(file_content)
            result = DE_CBC_PAD(messages, remainder, key)

        if mode == 'ECB' and block_mode == 'STE':
            messages, remainder = read_file_STE(file_content)
            result, remainder = DE_ECB_STE(messages, remainder, key)
            session['remainder'] = remainder

        if mode == 'CBC' and block_mode == 'STE':
            messages, remainder = read_file_STE(file_content)
            result, remainder = DE_CBC_STE(messages, remainder, key)
            session['remainder'] = remainder
        end_time = time.time()
        run_time = end_time - start_time

        # 将加密结果转换为适合存储在session中的格式
        session['result'] = result
        session['block_mode'] = block_mode
        session['run_time']=run_time

        return redirect(url_for('de_result'))

    return render_template('decode.html')


# 显示加密结果页面
@app.route('/en_result')
def en_result():
    time=session.get('run_time')
    encrypted_data = session.get('result')
    return render_template('en_result.html', result=encrypted_data,time=time)


# 显示解密结果页面
@app.route('/de_result')
def de_result():
    encrypted_data = session.get('result')
    time=session.get('run_time')
    messages = []
    for c in encrypted_data:
        num_bytes = (c.bit_length() + 7) // 8
        int_bytes = c.to_bytes(num_bytes, 'big')
        message = int_bytes.decode('utf-8')
        message = message[::-1]
        messages.append(message)

    return render_template('de_result.html', result=messages,time=time)


# 下载解密结果页面
@app.route('/download_de')
def download_file_de():
    encrypted_data = session.get('result')

    if not encrypted_data:
        return "No encrypted data available for download", 404

    # 创建一个BytesIO对象来存储加密结果
    file_data = io.BytesIO()
    write_file(file_data, encrypted_data)
    file_data.seek(0)  # 重置文件指针到开始位置

    return send_file(
        file_data,
        mimetype='text/plain',
        as_attachment=True,
        download_name='result.bin'  # 使用 download_name 而不是 attachment_filename
    )


# 下载加密结果文件
@app.route('/download_en')
def download_file_en():
    encrypted_data = session.get('result')
    block_mode = session.get('block_mode')
    remainder = session.get('remainder')
    if not encrypted_data:
        return "No encrypted data available for download", 404

    # 创建一个BytesIO对象来存储加密结果
    file_data = io.BytesIO()
    if block_mode == 'PAD':
        write_file(file_data, encrypted_data)
        file_data.seek(0)  # 重置文件指针到开始位置
    if block_mode == 'STE':
        write_file_STE(file_data, encrypted_data, remainder)
        file_data.seek(0)  # 重置文件指针到开始位置

    return send_file(
        file_data,
        mimetype='text/plain',
        as_attachment=True,
        download_name='result.bin'  # 使用 download_name 而不是 attachment_filename
    )


if __name__ == '__main__':
    app.run(debug=True)
