import xlwings as xw
import pandas as pd
import openpyxl as op
from xlwings.constants import Direction  # Testing the function of last cell

### reading files using xlwings
order = xw.Book(r'C:\Users\YIEN\Desktop\to Will\行網 - QS Connection\COH - SampleOrders_20190502.xlsx')
receive = xw.Book(r'C:\Users\YIEN\Desktop\to Will\行網 - QS Connection\AMDOCS - 行網收款紀錄_20190430.xlsx')
price = xw.Book(r'C:\Users\YIEN\Desktop\to Will\行網 - QS Connection\COH - 行網資費方案價格主檔.xlsx')
cust= xw.Book(r'C:\Users\YIEN\Desktop\to Will\行網 - QS Connection\MDM - 行網客戶主檔.xlsx')

#reading files using pandas to make it become dataframe
orderpd = pd.read_excel (r'C:\Users\YIEN\Desktop\to Will\行網 - QS Connection\COH - SampleOrders_20190502.xlsx')
receivepd = pd.read_excel(r'C:\Users\YIEN\Desktop\to Will\行網 - QS Connection\AMDOCS - 行網收款紀錄_20190430.xlsx')
pricepd = pd.read_excel(r'C:\Users\YIEN\Desktop\COH - 行網資費方案價格主檔.xlsx')
custpd = pd.read_excel(r'C:\Users\YIEN\Desktop\to Will\行網 - QS Connection\MDM - 行網客戶主檔.xlsx')
billpd = pd.read_excel(r'C:\出帳.xlsx')
regionpd = pd.read_excel(r'C:\Users\YIEN\Desktop\to Will\行網 - QS Connection\Retail_Emp_For_NPV.xlsx')

### selecting main sheets
order_sheet = order.sheets['order']
receive_sheet = receive.sheets['工作表1']
price_sheet = price.sheets['sheet 1']
cust_sheet = cust.sheets['工作表1']

### Merging test
result = receivepd.merge(custpd, on="ACCOUNT_ID", how='left')
    #print(result)
result2 = result.merge(orderpd, on="MSISDN", how='left')
print(result2)
result3 = result2.merge(pricepd, on="PROMOTIONCODE", how='left')
print(result3)
result4 = result3.merge(billpd, on="ACCOUNT_ID", how='left')
### Output the dataframe to excel and save it at C:\USER\YIEN
result4.to_excel('result4.xlsx', index=False)

result4_region = result4.merge(regionpd, on="店組/人員代號")

## select some columns
newdf = result.iloc[:,0:2]
print(newdf)

### Finding and coloring the last cell of the sheet
order_last_cell = order_sheet.cells(1,"A").end(Direction.xlDown)
order_last_cell.color = (255,0,0)
print(order_last_cell.row)
print(order_last_cell.column)

temp = result4_region[result4_region['店組/人員代號']==2925].groupby(by = 'PAYMENT_ID')['PAY_AMOUNT'].sum()
sum(temp)
temp2 = result4_region[result4_region['店組/人員代號']==2925].groupby(by = 'MSISDN_x')['AMOUNT'].sum()
sum(temp2)

###
end_cell = result4.cells(1,"A").end(Direction.xlDown)
end_row = 3048

s=0
s2=0
#row = 1
#r = 1
pid = set(result4.PAYMENT_ID)
for i in pid:
    s=s+(result4[result4['PAYMENT_ID'] == i]['PAY_AMOUNT'].values[0])

pid2 = set(result4_region.PAYMENT_ID)
for i in pid2:
    s2=s2+(result4_region[result4_region['PAYMENT_ID'] == i]['PAY_AMOUNT'].values[0])

temp = result4[result4['ACCOUNT_ID']==843840142].groupby(by = 'PAYMENT_ID')['PAY_AMOUNT'].sum()
#temp = result4[result4['ACCOUNT_ID']==843840142]['PAY_AMOUNT'].sum()
set(temp)
sum(temp)
temp2 = result4[result4['ACCOUNT_ID']==843840242].groupby(by = 'MSISDN_x')['AMOUNT'].sum()
sum(temp2)

Z = result4[result4['PAYMENT_ID'] == 17247494917]['PAY_AMOUNT']