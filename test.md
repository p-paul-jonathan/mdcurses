# Fraudulent Claim Detection: Analysis Report

## Problem Statement

Global Insure, a leading insurance company, faces significant financial losses due to fraudulent claims. The current manual inspection process is inefficient and often detects fraud too late. The objective is to build a data-driven model to classify claims as fraudulent or legitimate early in the process, using historical claim details and customer profiles.

---

## 1. Data Preparation

- **Loaded** the dataset and explored its structure, dimensions, and data types.
- **Previewed** the data and reviewed the data dictionary for all features.

---

## 2. Data Cleaning

- **Handled Null Values:**
  - Dropped columns with all null values (e.g., `_c39`).
  - Filled missing values in categorical columns (e.g., `authorities_contacted`).
- **Removed Redundant/Invalid Data:**
  - Dropped columns with high uniqueness (identifiers).
  - Removed rows with illogical values (e.g., negative amounts).
- **Fixed Data Types:**
  - Converted date columns to datetime format.

---

## 3. Train-Validation Split

- **Split** the data into 70% training and 30% validation sets using stratified sampling to preserve class balance.
- **Defined** feature matrix `X` and target vector `y`.

Example

```python
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.33, random_state=42)
```

---

## 4. Exploratory Data Analysis (EDA)

### 4.1 Univariate Analysis

- **Visualized** distributions of numerical features (histograms).
- **Identified** skewed features and potential outliers.

### 4.2 Correlation Analysis

- **Generated** a correlation heatmap to identify multicollinearity among numerical features.

### 4.3 Class Balance

- **Checked** the distribution of the target variable (`fraud_reported`).
- **Observed** class imbalance (fewer fraudulent claims).

### 4.4 Bivariate Analysis

- **Categorical Features:**
  - Analyzed likelihood of fraud for each category level.
  - Identified non-informative categories.
- **Numerical Features:**
  - Used boxplots to compare distributions by fraud status.

---

