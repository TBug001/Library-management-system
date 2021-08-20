using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BookMS
{
    public partial class login : Form
    {
        public login()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(textBox1.Text!=""&&textBox2.Text!="")
            {
                Login();
            }
            else
            {
                MessageBox.Show("输入为空，请重新输入");
            }
        }
        //登录是否被允许，允许登录返回真
        public void Login()
        {
            //用户
            if (radioButtonUser.Checked == true)
            {
                Dao dao = new Dao();
                string sql= string.Format("select * from t_user where uid='{0}'and psw='{1}'", textBox1.Text, textBox2.Text);
                IDataReader dc = dao.read(sql);
                if (dc.Read())
                {
                    Data.UID = dc["uid"].ToString();
                    Data.UName = dc["uname"].ToString();
                    MessageBox.Show("登录成功");
                    user1 user = new user1();
                    this.Hide();
                    user.ShowDialog();
                    this.Show();
                }
                else
                {
                    MessageBox.Show("账号或密码错误，登录失败!");
                }
                dao.DaoClose();
            }
            
            //管理员
            if(radioButtonAdmin.Checked==true)
            {
                Dao dao = new Dao();
                string sql = string.Format("select * from t_admin where adid='{0}'and psw='{1}'", textBox1.Text, textBox2.Text);
                IDataReader dc = dao.read(sql);
                if (dc.Read())
                {
                    MessageBox.Show("登录成功");
                    admin1 a= new admin1();
                    this.Hide();
                    a.ShowDialog();
                    this.Show();
                }
                else
                {
                    MessageBox.Show("账号或密码错误，登录失败!");
                }
                dao.DaoClose();
            }
        }

        private void login_Load(object sender, EventArgs e)
        {

        }
    }
}
