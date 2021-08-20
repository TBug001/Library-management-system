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
    public partial class admin23 : Form
    {
        public admin23()
        {
            InitializeComponent();
            Table();
        }
        public void Table()
        {
            dataGridView1.Rows.Clear();//清空旧数据
            Dao dao = new Dao();
            string sql = $"select * from t_buy";
            IDataReader dc = dao.read(sql);
            while (dc.Read())
            {
                dataGridView1.Rows.Add(dc[0].ToString(), dc[1].ToString(), dc[2].ToString(), dc[3].ToString(), dc[4].ToString());
            }
            dc.Close();
            dao.DaoClose();
        }
        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string id = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();//获取书号
            string name = dataGridView1.SelectedRows[0].Cells[1].Value.ToString();
            string author = dataGridView1.SelectedRows[0].Cells[2].Value.ToString();
            string press = dataGridView1.SelectedRows[0].Cells[3].Value.ToString();
            Dao dao = new Dao();
            string a = $"select bid from t_book where '{id}'=bid";
            IDataReader dc = dao.read(a);
            string aa = null;
            while (dc.Read())
            {
                aa=dc[0].ToString();
            }
            if (id != aa)
            {
                string sql = $"insert into t_book(bid,bname,author,press,number)values('{id}','{name}','{author}','{press}',1)";
                int b=dao.Execute(sql);
                if (b > 0)
                {
                    MessageBox.Show("购买成功");
                }
                else
                {
                    MessageBox.Show("购买失败！");
                }
            }
            else
            {
                string c= $"update t_book set number=number+1 where bid='{id}'";
                int d=dao.Execute(c);
                if (d > 0)
                {
                    MessageBox.Show("购买成功");
                }
                else
                {
                    MessageBox.Show("购买失败！");
                }
            }
            

        }

        private void admin23_Load(object sender, EventArgs e)
        {

        }
    }
}
