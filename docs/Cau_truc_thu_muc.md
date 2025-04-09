```bash
/login-wallet-console
|
|-- /src                      # Source code
|   |-- /models               # Data models
|   |   |-- User.h            # User class declaration
|   |   |-- User.cpp          # User class implementation
|   |   |-- Wallet.h
|   |   |-- Wallet.cpp
|   |   |-- Transaction.h
|   |   |-- Transaction.cpp
|   |
|   |-- /managers
|   |   |-- UserManager.h        # Business logic managers
|   |   |-- UserManager.cpp
|   |   |-- WalletManager.h
|   |   |-- WalletManager.cpp
|   |   |-- TransactionManager.h
|   |   |-- TransactionManager.cpp
|   |   |-- OTPManager.h
|   |   |-- OTPManager.cpp
|   |   |-- BackupMananger.h
|   |   |-- BackupManager.cpp
|   |
|   |-- /utils                # Utility functions
|   |   |-- HashUtils.h       # Password hashing
|   |   |-- HashUtils.cpp
|   |   |-- FileUtils.h       # File operations
|   |   |-- FileUtils.cpp
|   |
|   |-- /views                # Console UI components
|   |   |-- Menu.h            # Base menu class
|   |   |-- Menu.cpp
|   |   |-- LoginMenu.h       # Login screen
|   |   |-- LoginMenu.cpp
|   |   |-- UserMenu.h        # Regular user menu
|   |   |-- UserMenu.cpp
|   |   |-- AdminMenu.h       # Admin user menu
|   |   |-- AdminMenu.cpp
|   |   |-- WalletMenu.h      # Wallet operations menu
|   |   |-- WalletMenu.cpp
|   |   |-- BackupMenu.h      # Backup operations menu
|   |   |-- BackupMenu.cpp
|   |
|   |-- Application.h         # Main application controller
|   |-- Application.cpp
|   |-- main.cpp              # Entry point
|
|-- /data                     # Data storage
|   |-- userData.csv             # User data file
|   |-- walletData.csv           # Wallet data
|   |-- transactionData.csv      # Transaction history
|   |-- /backup               # Backup directory
|
|-- /tests                    # Simple tests (optional)
|   |-- test_feature.cpp
|   |-- test_user.cpp
|   |-- test_wallet.cpp
|   |-- test_transaction.cpp
|
|-- README.md                 # Documentation
```
