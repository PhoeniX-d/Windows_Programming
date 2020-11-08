'for Form'
Imports System.Windows.Forms
' .Net Callable dll created using tlbimp.exe utility'
Imports AutomationServerTypeLibForDotNet

Public Class VBAutomation
    Inherits Form
    Public Sub New()
        Dim MyDispatch As Object
        Dim MyRef As New CMyMathClass
        MyDispatch = MyRef
        Dim iNum1 = 175
        Dim iNum2 = 125
        Dim iSum = MyDispatch.SumOfTwoIntegers(iNum1, iNum2)
        Dim str As String = String.Format("Sum of {0} and {1} is {2}", iNum1, iNum2, iSum)
        MsgBox(str)
        Dim iSub = MyDispatch.SubtractionOfTwoIntegers(iNum1, iNum2)
        str = String.Format("Subtraction of {0} and {1} is {2}", iNum1, iNum2, iSub)
        MsgBox(str)
        End
    End Sub

    <STAThread()>
    Shared Sub Main()
        Application.EnableVisualStyles()
        Application.Run(New VBAutomation)
    End Sub
End Class
