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
    public partial class admin22 : Form
    {
        string ID = "";
        public admin22()
        {
            InitializeComponent();
        }
        public admin22(string bid,string bname,string author,string press,string number)
        {
            InitializeComponent();
            ID=textBox1.Text = bid;
            textBox2.Text = bname;
            textBox3.Text = author;
            textBox4.Text = press;
            textBox5.Text = number;
        }
        private void button1_Click(object sender, EventArgs e)
        {
            string sql = $"update t_book set bid='{textBox1.Text}',bname='{textBox2.Text}',author='{textBox3.Text}',press='{textBox4.Text}',number={textBox5.Text} where bid='{ID}'";
            Dao dao = new Dao();
            if (dao.Execute(sql) > 0)
            {
                MessageBox.Show("修改成功");
                this.Close();
            }
        }

        private void admin22_Load(object sender, EventArgs e)
        {

        }
    }
}
