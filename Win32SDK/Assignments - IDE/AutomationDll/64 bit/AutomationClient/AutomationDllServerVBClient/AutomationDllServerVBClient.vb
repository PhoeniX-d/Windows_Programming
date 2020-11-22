'for 'Form'
Imports System.Windows.Forms
' .Net callable dll created by using tlbimp.exe utillity
Imports AutomationDllServerTypeLibForDotNet

Public Class AutomationDllServerVBClient
    Inherits Form
    Public Sub New()
        Dim MyIDispatch As Object
        Dim MyRef As New CMyMathClass
        MyIDispatch = MyRef
        Dim iNum1 = 125
        Dim iNum2 = 100
        Dim iSum = MyIDispatch.SumOfTwoIntegers(iNum1, iNum2)
        Dim str As String = String.Format("Sum Of {0} and {1} Is {2}", iNum1, iNum2, iSum)
        'default message box with only 1 button of 'OK'
        MsgBox(str)
        Dim iSub = MyIDispatch.SubtractionOfTwoIntegers(iNum1, iNum2)
        str = String.Format("Subtraction Of {0} and {1} is {2}", iNum1, iNum2, iSub)
        MsgBox(str)
        ' Following statement i.e. 'End' works as DestroyWindow(hwnd)
        End
    End Sub

    <STAThread()>
    Shared Sub Main()
        Application.EnableVisualStyles()
        Application.Run(New AutomationDllServerVBClient())
    End Sub
End Class
