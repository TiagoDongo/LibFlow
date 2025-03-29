## v0.1.0-alpha - LibFlow (Alpha Preview)

**Primeira versão Alpha do LibFlow. Sistema de gerenciamento de bibliotecas desenvolvido como projeto pessoal em evolução contínua.**  

---

### Funcionalidades Implementadas
- ✅ **Operações CRUD (Create, Read, Update, Delete):**  
  - **Criação:**  
    - Livros (título, autor, edição)  
    - Usuários (nome, e-mail, telefone, curso)  
  - **Leitura:**  
    - Busca de livros/usuários por ID  
    - Listagem completa de livros/usuários  
  - **Atualização:**  
    - Livros: título, autor, edição  
    - Usuários: nome, e-mail, curso  
  - **Exclusão:**  
    - Remoção de livros/usuários por ID  

---

- ✅ **Gerenciamento de Dados:**  
  - **Carregamento de Listas:**  
    - 🗂️ *Modo único*: Carrega uma lista específica (ex: `/data/book_lists/Book_1.json`).  
    - 📂 *Modo completo*: Carrega todas as listas das pastas `/data/book_lists` e `/data/user_lists`.  
  - **Salvamento:** Dados em JSON (livros e usuários).  
  - **Remoção:** Exclusão de listas individuais.  

---

### Limitações Conhecidas
- ⚠️ **Validação:** Campos não possuem restrições (ex: e-mails inválidos são aceitos).  
- ⚠️ **CLI:** Funcionalidade limitada ao terminal do VSCode.  
- ⚠️ **Testes:** Ausência de testes automatizados.   

---

### Próximos Passos
- 🛠️ Implementar validação de campos obrigatórios e formatos.  
- 🛠️ Desenvolver testes unitários.  
- 🛠️ Expandir funcionalidades (empréstimos, devoluções, relatórios).
- 🛠️ Tentar implementar e integrar uma Base de Dados ao projeto  

---

### Contribuições são bem-vindas!
- 🐛 **Relatar bugs:** Crie uma `issue` com descrição clara do problema.  
- 💡 **Sugerir melhorias:** Crie uma `issue` com descrição da melhoria proposta.  
  