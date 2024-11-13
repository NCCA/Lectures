# Lecture 8 : ML Workflows
Jon Macey

jmacey@bournemouth.ac.uk

---

## Overview

- In this lecture we will look at the typical workflow for a machine learning project
- These steps are typical in all ML workflows
- Whilst we will concentrate on PyTorch other frameworks have a similar workflow

---

## Workflow

- Training a machine learning model involves several core processes that transform raw data into a functional model capable of making predictions or decisions. 
- The typical workflow for a machine learning project can be broken down into the following steps:
  - Data Collection
  - Data Preprocessing
  - Model Selection
  - Model Training
  - Model Evaluation
  - Model Deployment

--

## Define the Problem and Objectives

- Before starting a machine learning project, it is essential to define the problem and objectives.

- Objective: Clearly outline the purpose of the model 
  - classification, regression, clustering etc.
- Metrics: Determine the evaluation metrics (measure of performance).
  - accuracy, precision, recall, [F1-score](https://en.wikipedia.org/wiki/F-score), [MSE](https://en.wikipedia.org/wiki/Mean_squared_errors).

---

## Data Collection

- This is the data we need to train our model
- The sources are varied and can include:
  - Databases
  - APIs
  - Web scraping
  - Data files
  - Sensors

--

## Ethics in Data Collection

- Data collection is a critical step in the machine learning workflow, and it is essential to ensure that the data collected is ethical and unbiased.
- Understand the Purpose of the Data
  - Clearly define the purpose of the data collection and ensure it aligns with ethical principles.
  - Avoid collecting data that could disproportionately harm or disadvantage specific groups.

--

## Consent and Privacy

- Informed Consent: Ensure individuals are fully informed about how their data will be used and give explicit permission.
  - you know those big things you click when you sign up for a service that is usually consent for this!
- Anonymization: Remove or obfuscate Personally Identifiable Information (PII) to protect privacy.
- Data Compliance: Follow laws and regulations like GDPR, CCPA, or other applicable data protection frameworks.


--

## Inclusivity and Representativeness

- Ensure the dataset includes diverse groups to minimize bias and promote fairness
- Avoid datasets that over-represent dominant groups or under-represent minorities.

--

## Sources of Data

- Use data from reliable, ethical sources
  - use public sources with proper licenses ([Kaggle](https://www.kaggle.com/) [Open Data](https://dataportals.org/) )
  - research institutions and governmental organizations.
  - Crowdsourced datasets with explicit consent from contributors.
- Check documentation for transparency regarding how the data was collected and preprocessed.


--

## Ethical Guidelines

- There are a number of published guidelines 
  - [uk gov](https://www.gov.uk/guidance/understanding-artificial-intelligence-ethics-and-safety)
  - [IEEE Global Initiative on Ethics of Autonomous and Intelligent Systems](https://standards.ieee.org/industry-connections/ec/autonomous-systems.html)
  - [EU overview](https://www.europarl.europa.eu/RegData/etudes/BRIE/2019/640163/EPRS_BRI(2019)640163_EN.pdf)


--

## Transparency and Documentation

- Maintain detailed documentation of:
  - How the data was collected.
  - Who collected it.
  - The intended use.
  - Known limitations or biases.
- Transparency is essential for ensuring the data is used responsibly and ethically.

--

## Synthetic Data as an Alternative

- Generate synthetic data that mirrors real world distributions while avoiding the inclusion of sensitive or PII data.
- Validate synthetic data for fairness and representation.
- Use synthetic data to augment existing datasets and improve model performance.

--

## More Reading on Ethics

- https://www.nature.com/articles/s41599-020-0501-9
- https://ai.ethicsworkshop.org/Library/fairmlbook.pdf
- [Good Video on Ethics](https://youtu.be/qpp1G0iEL_c?si=vTk_YkMv53nnIx3w)


---

## Data Preprocessing

- Data Cleaning :
  - Handle missing values, outliers, and inconsistencies.
- Data Transformation :
  - Normalize, scale, or encode features.
- Feature Engineering :
  - Create new features, reduce dimensionality, select important features to improve performance
- Data Splitting :
  - Split the data into training, validation, and test sets.

--

## Training Dataset

- Used to train the model by allowing it to learn patterns, relationships, and features in the data.
  - Largest portion of the dataset ( 70-80% of overall dataset).
  - Includes labeled data (in supervised learning) for the model to learn the input-output mapping.

--

## Validation Dataset

- Used to evaluate the model during training to tune hyper-parameters and prevent over-fitting
  - Separate from the training dataset ( 10-20% of overall dataset).
  - Not seen by the model during training, but used during intermediate evaluations.

--

## Test Dataset

- Used to evaluate the final model’s performance after training and hyperparameter tuning are complete.
  - Completely separate from the training and validation datasets ( 10-15% of the dataset).
  - Simulates real-world data the model will encounter in production

---

## Model Selection

- Choose the appropriate model architecture and algorithm based on the problem and data.
- Considerations:
  - Type of problem (classification, regression, clustering).
  - Size and complexity of the dataset.
  - Computational resources available.
- More on this in other lectures

--

## Model Training

- Input the training dataset into the model
- Optimize model parameters using optimization techniques.
- 	Specify hyperparameters (e.g., learning rate, regularization strength) for fine-tuning.

--

## Hyperparameters

- A hyperparameter refers to a parameter whose value is set before the training process begins and controls the behavior of the learning algorithm. 
- Unlike model parameters (e.g., weights and biases in neural networks), hyperparameters are not learned from the data during training but are manually set or optimized separately.

--

## Hyperparameters

- Examples of hyperparameters include:
  - Learning rate
  - Regularization strength
  - Number of hidden layers
  - Number of neurons in each layer

---

## Validation and Hyperparameter Tuning

- Evaluate model performance on the validation set to check for overfitting or underfitting.
- Use validation metrics to guide adjustments in hyperparameters and features.
- Refine hyperparameters using techniques like grid search, random search, or Bayesian optimization.

---

## Model Evaluation

- Test the model on a separate test dataset to assess its performance and generalization capability.
- Compare the results against baseline models or industry benchmarks.


---

## Model Deployment

- Deploy the model in a production environment to make predictions on new, unseen data.
- Monitor the model’s performance and retrain periodically to maintain accuracy.


---

## Using PyTorch

- All of these processes can be done in PyTorch. 
- We are going to start with a simple Linear Regression example
- We will then move onto more complex examples and look at the different tools available in PyTorch
  - Dataloaders
  - Optimizers
  - Loss functions

---

## First Example

- The following example is a simple linear regression using the following notebook

[Simple Linear Regression](https://github.com/NCCA/SEForMedia/blob/main/LinearModel/LinearModel.ipynb)

