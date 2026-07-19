-- ============================================================
-- Nchabi Chickens
-- Database Name will be called NchabiFarm
-- Database Schema
--
-- Database: SQLite3
-- Author: Tebogo Makhubela
--
-- This schema is intentionally designed as a learning project
-- for:
--
-- • SQLite3
-- • Database relationships
-- • Repository Pattern
-- • REST APIs
-- • Modern C++
-- • Docker
-- • Azure
-- • Kubernetes
-- • OpenTofu
--
-- ============================================================

PRAGMA foreign_keys = ON;

-- ============================================================
-- CHICKENS
-- ============================================================

CREATE TABLE IF NOT EXISTS Chicken
(
    Id              INTEGER PRIMARY KEY AUTOINCREMENT,

    TagNumber       TEXT NOT NULL UNIQUE,

    Breed           TEXT NOT NULL,

    Gender          TEXT NOT NULL,

    HatchDate       TEXT,

    PurchaseDate    TEXT,

    WeightKg        REAL NOT NULL DEFAULT 0,

    Status          TEXT NOT NULL,

    Pen             TEXT,

    Notes           TEXT,

    CreatedAt       TEXT NOT NULL,

    UpdatedAt       TEXT NOT NULL
);

-- ============================================================
-- DAILY EGG PRODUCTION
-- ============================================================

CREATE TABLE IF NOT EXISTS EggProduction
(
    Id INTEGER PRIMARY KEY AUTOINCREMENT,

    ChickenId INTEGER NOT NULL,

    ProductionDate TEXT NOT NULL,

    GoodEggs INTEGER NOT NULL DEFAULT 0,

    BrokenEggs INTEGER NOT NULL DEFAULT 0,

    FOREIGN KEY (ChickenId)
    REFERENCES Chicken(Id)
    ON DELETE CASCADE
    );

-- ============================================================
-- CUSTOMERS
-- ============================================================

CREATE TABLE IF NOT EXISTS Customer
(
    Id INTEGER PRIMARY KEY AUTOINCREMENT,

    FirstName TEXT NOT NULL,

    LastName TEXT NOT NULL,

    Phone TEXT,

    Email TEXT,

    Address TEXT,

    CreatedAt TEXT NOT NULL
);

-- ============================================================
-- PRODUCTS
--
-- Examples:
-- Large Egg Tray
-- Medium Egg Tray
-- Broiler Chicken
-- Layer Chicken
-- Feed
-- ============================================================

CREATE TABLE IF NOT EXISTS Product
(
    Id INTEGER PRIMARY KEY AUTOINCREMENT,

    Name TEXT NOT NULL UNIQUE,

    Unit TEXT NOT NULL,

    SellingPrice REAL NOT NULL,

    Active INTEGER NOT NULL DEFAULT 1
);

-- ============================================================
-- INVENTORY
--
-- Current stock available.
-- ============================================================

CREATE TABLE IF NOT EXISTS Inventory
(
    Id INTEGER PRIMARY KEY AUTOINCREMENT,

    ProductId INTEGER NOT NULL UNIQUE,

    Quantity INTEGER NOT NULL DEFAULT 0,

    LastUpdated TEXT NOT NULL,

    FOREIGN KEY(ProductId)
    REFERENCES Product(Id)
    );

-- ============================================================
-- SALES ORDERS
-- ============================================================

CREATE TABLE IF NOT EXISTS SalesOrder
(
    Id INTEGER PRIMARY KEY AUTOINCREMENT,

    CustomerId INTEGER NOT NULL,

    OrderDate TEXT NOT NULL,

    Status TEXT NOT NULL,

    Total REAL NOT NULL DEFAULT 0,

    FOREIGN KEY(CustomerId)
    REFERENCES Customer(Id)
    );

-- ============================================================
-- SALES ORDER ITEMS
-- ============================================================

CREATE TABLE IF NOT EXISTS SalesOrderItem
(
    Id INTEGER PRIMARY KEY AUTOINCREMENT,

    SalesOrderId INTEGER NOT NULL,

    ProductId INTEGER NOT NULL,

    Quantity INTEGER NOT NULL,

    UnitPrice REAL NOT NULL,

    LineTotal REAL NOT NULL,

    FOREIGN KEY(SalesOrderId)
    REFERENCES SalesOrder(Id)
    ON DELETE CASCADE,

    FOREIGN KEY(ProductId)
    REFERENCES Product(Id)
    );

-- ============================================================
-- DELIVERY
-- ============================================================

CREATE TABLE IF NOT EXISTS Delivery
(
    Id INTEGER PRIMARY KEY AUTOINCREMENT,

    SalesOrderId INTEGER NOT NULL UNIQUE,

    DriverName TEXT,

    Vehicle TEXT,

    DeliveryAddress TEXT,

    DeliveryDate TEXT,

    Status TEXT,

    FOREIGN KEY(SalesOrderId)
    REFERENCES SalesOrder(Id)
    );

-- ============================================================
-- INDEXES
-- ============================================================

CREATE INDEX IF NOT EXISTS IDX_Chicken_Tag
    ON Chicken(TagNumber);

CREATE INDEX IF NOT EXISTS IDX_EggProduction_Date
    ON EggProduction(ProductionDate);

CREATE INDEX IF NOT EXISTS IDX_EggProduction_Chicken
    ON EggProduction(ChickenId);

CREATE INDEX IF NOT EXISTS IDX_Product_Name
    ON Product(Name);

CREATE INDEX IF NOT EXISTS IDX_Customer_LastName
    ON Customer(LastName);

CREATE INDEX IF NOT EXISTS IDX_SalesOrder_Customer
    ON SalesOrder(CustomerId);

CREATE INDEX IF NOT EXISTS IDX_SalesOrder_Date
    ON SalesOrder(OrderDate);

CREATE INDEX IF NOT EXISTS IDX_OrderItem_Order
    ON SalesOrderItem(SalesOrderId);

CREATE INDEX IF NOT EXISTS IDX_OrderItem_Product
    ON SalesOrderItem(ProductId);

CREATE INDEX IF NOT EXISTS IDX_Delivery_Status
    ON Delivery(Status);