#include <stdio.h>
#include <windows.h>
#include <oledb.h>
#include <ole2.h>
#include <initguid.h> // Inclua esta diretiva de inclusão para definir CLSID_MSDASQL

// Defina a constante CLSID_MSDASQL
DEFINE_GUID(CLSID_MSDASQL, 0xc8b521fb, 0x5cf3, 0x11ce, 0xad, 0xe5, 0x00, 0xaa, 0x00, 0x5f, 0xff, 0x2f);

int main() {
    // Inicialize a biblioteca COM
    CoInitialize(NULL);

    // Crie a interface do OLEDB e a conexão
    IUnknown *pIUnknown = NULL;
    IDBInitialize *pIDBInitialize = NULL;

    // Inicialize a interface OLEDB
    CoCreateInstance(&CLSID_MSDASQL, NULL, CLSCTX_INPROC_SERVER, &IID_IUnknown, &pIUnknown);
    pIUnknown->QueryInterface(IID_IDBInitialize, &pIDBInitialize);

    // Configure a conexão OLEDB para o Microsoft Access
    pIDBInitialize->Initialize();

    // Defina a string de conexão para o Microsoft Access
    WCHAR *connectionString = L"Provider=Microsoft.ACE.OLEDB.12.0;Data Source=C:\\caminho\\para\\seu\\arquivo.accdb;";
    pIDBInitialize->SetProperties(1, &DBPROP_INIT_DATASOURCE, connectionString, 0, NULL);

    // Crie a interface de sessão
    IDBCreateSession *pIDBCreateSession = NULL;
    pIDBInitialize->QueryInterface(IID_IDBCreateSession, &pIDBCreateSession);

    // Abra uma sessão
    IDBSession *pIDBSession = NULL;
    pIDBCreateSession->CreateSession(NULL, IID_IDBCreateSession, &pIDBSession);

    // Execute comandos SQL para inserir dados no Access
    IOpenRowset *pIOpenRowset = NULL;
    pIDBSession->QueryInterface(IID_IOpenRowset, &pIOpenRowset);

    // Exemplo de comando SQL para inserir dados em uma tabela
    WCHAR *sqlCommand = L"INSERT INTO SuaTabela (Campo1, Campo2) VALUES ('Valor1', 'Valor2')";
    IRowset *pIRowset = NULL;
    pIOpenRowset->OpenRowset(NULL, &DBID_NULL, NULL, IID_IRowset, 0, NULL, (IUnknown**)&pIRowset, NULL, NULL, NULL);

    // Execute o comando SQL
    pIRowset->QueryInterface(IID_IAccessor, &pIAccessor);
    pIAccessor->CreateAccessor(DBACCESSOR_ROWDATA, 0, NULL, 0, &hAccessor, NULL);
    pIRowset->QueryInterface(IID_IAccessor, &pIAccessor);
    pIAccessor->CreateAccessor(DBACCESSOR_ROWDATA, 0, NULL, 0, &hAccessor, NULL);

    HROW hRow;
    pIRowset->InsertRow(hAccessor, pData, &hRow);
    pIRowset->ReleaseRows(1, &hRow, NULL, NULL, NULL);

    // Libere recursos
    pIDBInitialize->Release();
    pIDBSession->Release();
    pIDBCreateSession->Release();
    pIUnknown->Release();
    CoUninitialize();

    return 0;
}

